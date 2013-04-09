#! /usr/bin/python3
import re

f = open("../doc/g14_prof_report.tex")
report = f.read()
f.close()
title = re.search(".*\\\\title(.*)\\\\maketitle.*",report,re.S)
title = title.group(1).strip()
title = re.sub("\s+"," ",title)
title = re.findall("{([^}]*)}",title,re.S)
html_title = title[0]
authors = title[1]
authors = authors.split("\\and")
author1 = authors[0].strip()
author2 = authors[1].strip()
author3 = authors[2].strip()
author1 = author1.split("\\\\")
author2 = author2.split("\\\\")
author3 = author3.split("\\\\")
author1 = author1[0:2]
author2 = author2[0:2]
author3 = author3[0:2]
body = report.split("\\section")
introduction = body[1]
introduction = re.sub("{.*}","",introduction,re.S)
introduction = introduction.strip()
plots = body[2]
plots = plots.split("\\subsection")
section_title = re.sub("[^A-Za-z ]","",plots[0])
subsection_titles = []
subsection_body = []
subsection_images = []
plots = plots[1:]
for subsection in plots:
	temp = re.search("[^{]*{([^}]*)}(.*)",subsection,re.S)
	tempImg = []
	subsection_titles.append(temp.group(1))
	temp = subsection.split("\\includegraphics")
	if len(temp) == 1:
		temp2 = re.search("{.*}(.*)",temp[0],re.S)
		subsection_body.append(temp2.group(1).strip())
	if len(temp) == 2:
		temp2 = re.search("[^{]*{([^}]*)}.*\\\\end.*{figure}(.*)",temp[1],re.S)
		subsection_body.append(temp2.group(2))
		tempImg.append(temp2.group(1))
	if len(temp) == 3:
		temp2 = re.search("[^{]*{([^}]*)}.*",temp[1],re.S)
		tempImg.append(temp2.group(1))
		temp2 = re.search("[^{]*{([^}]*)}.*\\\\end.*{figure}(.*)",temp[2],re.S)
		subsection_body.append(temp2.group(2))
		tempImg.append(temp2.group(1))
	subsection_images.append(tempImg)

f = open("../doc/g14_lab09_report.html",'w')
f.write("<!DOCTYPE html>" + "\n" + ("<html>") + "\n" + ("<head>") + "\n" + ("<title>") + "\"" + html_title + "\"" + ("</title>") + ("</head>" + "\n" + ("<body>") + "\n" + ("<div>") + "\n" + "<center>" + ("<h1>") + "Analysis of Performance Plots Obtained by Repeated Runs of the Base Code" + ("</h1>") + "</center>" + "\n"))
f.write("<h3>" + "<center>" + author1[0] + "<br>" + author1[1] + "<br>" + author2[0] + "<br>" + author2[1] + "<br>" + author3[0] + "<br>" + author3[1] + "</center>" + "</h3>")
j = 1
for i in range(0,len(subsection_images)):
	f.write( "<center>" + "<h2>" + subsection_titles[i] + ("</h1>") + "</center>" + "\n")
	for img in subsection_images[i]:
		f.write( "<center>" + "<img" + " " + ("src=") + "\"" + "../plots/" + "g14_lab09_plot0" + str(j) + ".png" + "\"" + (">") + ("</img>") + "</center>" + "\n" + "\n")
		j = j+1;
	f.write(("<p>") + "<center>" + "\n" + subsection_body[i] + "</center>" + ("</p>") + ("<hr>") + "\n")
f.write(("</div>") + "\n" + ("</body>") + "\n" + ("</html>"))
