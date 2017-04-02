<?php

define('SUCCESS', 0);
define('ERR_INVALID_USER', -1);
define('ERR_INVALID_PASS', -2);
define('ERR_UNCONFIRMED', -3);
define('ERR_INVALID_HASH', -4);
define('ERR_UNKNOWN', -99);

//login/logout functions

function login($username, $password) {
	$hashedpw = md5($password);
	$result = get_db()->query(sprintf("SELECT oid,username,password,active FROM users WHERE username='%s' AND password='%s'",$username,$hashedpw));

	if ($result === FALSE || $result === TRUE) {
		return ERR_UNKNOWN;
	}
	$row = $result->fetchArray();
	if ($row == 0) return ERR_INVALID_PASS;
	if ($row['active'] == 0) return ERR_UNCONFIRMED;
	$_SESSION['id'] = $row['rowid'];
	return SUCCESS;
}

function logout() {
	session_name('CS458');
	session_start();
	session_destroy();
	header('Location: index.php');
	exit(0);
}

function confirm($hash) {
	$result = get_db()->query(sprintf("SELECT oid,username,confirm FROM users WHERE confirm='%s'", get_db()->escapeString($hash)));

	if ($result === FALSE || $result === TRUE) {
		return ERR_UNKNOWN;
	}
	$row = $result->fetchArray();
	if ($row == 0) return ERR_INVALID_HASH;
	get_db()->exec(sprintf("UPDATE users SET confirm = '', active = 1 WHERE users.oid = %d",$row['rowid']));
	$_SESSION['id'] = $row['rowid'];
	return SUCCESS;
}

//random query functions
function get_guest_id() {
	$result = get_db()->query(sprintf("SELECT oid FROM users WHERE username = 'guest'"));
	$row = $result->fetchArray();
	return $row['rowid'];
}

function is_guest() {
	return $_SESSION['id'] == get_guest_id();
}

function get_id() {
	return $_SESSION['id'];
}

function get_username() {
	$result = get_db()->query(sprintf("SELECT username FROM users WHERE oid = %d",get_id()));
	$row = $result->fetchArray();
	return $row['username'];
}

function can_vote($uid) {
	$result = get_db()->query(sprintf('SELECT perms.can_vote AS result FROM perms INNER JOIN ref ON ref.id_perm = perms.oid INNER JOIN users ON ref.id_user = users.oid WHERE users.oid=%d',$uid));
	$row = $result->fetchArray();
	return ($row['result'] == 1);
}

function can_link() {
	if (is_guest()) return FALSE;
	$result = get_db()->query(sprintf('SELECT perms.can_link AS result FROM perms INNER JOIN ref ON ref.id_perm = perms.oid INNER JOIN users ON ref.id_user = users.oid WHERE users.oid=%d',$_SESSION['id']));
	$row = $result->fetchArray();
	return ($row['result'] == 1);
}

function can_article() {
	if (is_guest()) return FALSE;
	$result = get_db()->query(sprintf('SELECT perms.can_article AS result FROM perms INNER JOIN ref ON ref.id_perm = perms.oid INNER JOIN users ON ref.id_user = users.oid WHERE users.oid=%d',$_SESSION['id']));
	$row = $result->fetchArray();
	return ($row['result'] == 1);
}

function can_comment() {
	if (is_guest()) return FALSE;
	$result = get_db()->query(sprintf('SELECT perms.can_comment AS result FROM perms INNER JOIN ref ON ref.id_perm = perms.oid INNER JOIN users ON ref.id_user = users.oid WHERE users.oid=%d',$_SESSION['id']));
	$row = $result->fetchArray();
	return ($row['result'] == 1);
}

function can_file() {
        if (is_guest()) return FALSE;
        $result = get_db()->query(sprintf('SELECT perms.can_file AS result FROM perms INNER JOIN ref ON ref.id_perm = perms.oid INNER JOIN users ON ref.id_user = users.oid WHERE users.oid=%d',$_SESSION['id']));
        $row = $result->fetchArray();
        return ($row['result'] == 1);
}

function get_content_list($start = 0, $limit = 30) {
	$result = get_db()->query(sprintf('SELECT content.oid AS id,content.id_type AS type,users.username AS author,content.title AS title,content.content AS content,content.timestamp AS modified,(SELECT COUNT(*) FROM votes WHERE votes.id_content = content.oid AND type = 1) AS upvotes,(SELECT COUNT(*) FROM votes WHERE votes.id_content = content.oid AND type = 0) AS downvotes FROM content INNER JOIN users ON users.oid = content.id_author WHERE content.id_type >= 1 AND content.id_type <=3 ORDER BY content.oid ASC LIMIT %d,%d',$start,$limit));

	$array = array();
	while ($row = $result->fetchArray()) {
		$row['commentcount'] = get_comment_count($row['id']);
		array_push($array, $row);
	}
	return $array;
}

function get_content($id) {
	$result = get_db()->query(sprintf('SELECT content.oid AS id,content.id_type AS type,users.username AS author,content.title AS title,content.content AS content,content.timestamp AS modified,(SELECT COUNT(*) FROM votes WHERE votes.id_content = content.oid AND type = 1) AS upvotes,(SELECT COUNT(*) FROM votes WHERE votes.id_content = content.oid AND type = 0) AS downvotes FROM content INNER JOIN users ON users.oid = content.id_author WHERE content.oid = %d', $id));

	$row = $result->fetchArray();
	if (count($row) == 0) return array();
	$row['commentcount'] = get_comment_count($row['id']);
	return $row;
}

function get_comments_for_id($id) {
	$result = get_db()->query(sprintf('SELECT content.oid AS id,users.username AS author,content.title AS title,content.content AS content,content.timestamp AS modified,(SELECT COUNT(*) FROM votes WHERE votes.id_content = content.oid AND type = 1) AS upvotes,(SELECT COUNT(*) FROM votes WHERE votes.id_content = content.oid AND type = 0) AS downvotes FROM content INNER JOIN users ON users.oid = content.id_author WHERE content.id_type = 4 AND content.id_parent = %d',$id));

	$array = array();
	while ($row = $result->fetchArray()) {
		array_push($array, $row);
	}
	for ($i = 0; $i < count($array); $i++) {
		$array[$i]['children'] = get_comments_for_id($array[$i]['id']);
	}
	return $array;
}

function get_comment_count($id) {
	$query = sprintf('SELECT content.oid AS id FROM content WHERE content.id_type = 4 AND content.id_parent = %d',$id);
	$result = get_db()->query($query);
	$array = array();
	$count = 0;
	while ($row = $result->fetchArray()) {
		array_push($array, $row);
	}
	for ($i = 0; $i < count($array); $i++) {
		$count += get_comment_count($array[$i]['id']);
		$count++;
	}
	
	return $count;
}

//acting functions

function upvote($uid, $id) {
	get_db()->exec(sprintf('INSERT INTO votes (id_author,id_content,type) VALUES(%d,%d,1)',$uid,$id));
}

function downvote($uid, $id) {
	get_db()->exec(sprintf('INSERT INTO votes (id_author,id_content,type) VALUES(%d,%d,0)',$uid,$id));
}

function put_link($title, $content) {
	get_db()->exec(sprintf("INSERT INTO CONTENT (id_author, id_type, id_parent, timestamp, title, content) VALUES (%d,2,0,strftime('%%s','now'),'%s','%s')",$_SESSION['id'],get_db()->escapeString($title),get_db()->escapeString($content)));
}

function put_article($title, $content) {
	get_db()->exec(sprintf("INSERT INTO CONTENT (id_author, id_type, id_parent, timestamp, title, content) VALUES (%d,1,0,strftime('%%s','now'),'%s','%s')",$_SESSION['id'],get_db()->escapeString($title),get_db()->escapeString($content)));

}

function put_comment($id, $title, $content) {
	get_db()->exec(sprintf("INSERT INTO CONTENT (id_author, id_type, id_parent, timestamp, title, content) VALUES (%d,4,%d,strftime('%%s','now'),'%s','%s')",$_SESSION['id'],$id,get_db()->escapeString($title),get_db()->escapeString($content)));
}

function put_file($title, $content) {
	//echo $content;
        get_db()->exec(sprintf("INSERT INTO CONTENT (id_author, id_type, id_parent, timestamp, title, content) VALUES (%d,3,0,strftime('%%s','now'),'%s','%s')",$_SESSION['id'],get_db()->escapeString($title),get_db()->escapeString($content)));
}


?>