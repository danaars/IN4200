
infile = open("web-stanford.txt", "r")
outfile = open("web-stanford_new.txt", "w")

for i in range(4):
    outfile.write(infile.readline())

for line in infile:
    fromnode, tonode = line.split()
    outfile.write(f"{int(fromnode)-1}\t{int(tonode)}\n")

infile.close()
outfile.close()
