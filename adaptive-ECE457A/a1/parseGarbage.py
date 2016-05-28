with open("garbage.txt") as f:
    content = f.readlines()

unfucked = []
unfucked.append("")
unfucked.append("")
unfucked.append("")
unfucked.append("")

for i, line in enumerate(content):
	unfucked[i%4] += line.strip()

print unfucked[0].strip()
print unfucked[1].strip()
print unfucked[2].strip()
print unfucked[3].strip()

