if ARGV.size == 2
  theirExec = ARGV.first
  myExec = ARGV.last
else
  puts "Expected command: tests.rb THEIREXECUTABLE YOUREXECUTABLE"
  exit
end

words = []
File.readlines('words.txt').each do |line|
  words << line
end
words = words.select{|word| word.length > 5}

tests = []
letters = []
26.times { |i| letters << (i + 97).chr }
letters += letters
random = 0
command = ""
mostCommon = "etaoinshr"
100.times do
  random = (rand*200).to_i
  command = mostCommon.split("").shuffle.join("\n") + letters.shuffle.join("\n")
  tests << system("echo \"#{ command }\" | ./#{theirExec} words.txt #{random} > theiroutput.txt && echo \"#{ command }\" | ./#{myExec} words.txt #{random} > myoutput.txt && diff -y theiroutput.txt myoutput.txt")
  break unless tests.last
  puts "\n\n"
end
sample = ""
10.times do
  random = (rand*200).to_i
  sample = words.sample
  tests << system("echo \"#{ sample + "\n + n\n"}\" | ./#{theirExec} words.txt #{random} > theiroutput.txt && echo \"#{ words.sample }\" | ./#{myExec} words.txt #{random} > myoutput.txt && diff -y theiroutput.txt myoutput.txt")
  unless tests.last
    puts "random: #{random} word: #{sample}"
    break
  end
end

if tests.all?
  puts "\nAll passed"
else
  puts "\nDid not pass #{tests.count}"
end
