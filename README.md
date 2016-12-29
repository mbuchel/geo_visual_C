# GEO VISUAL C

This is a simple project I finished to optimize some javascript code for my mom, for doing some getis hotspot analysis on time as the property of interest.

Compilation is simple, just run "make all", in the terminal at the location you wish to run it, currently it was tested with "\n" as the delimiter, however there is code allowing proper CSV format with an CRLF code as the delimiter, all spaces and tabs are ignored in the input file. Current use of the project just involves a command line implentation of "./out name\_of\_file\_in name\_of\_file\_out". I may optimize this later on, if it is necessary, so far the algorithms I used where fairly straight forward and only provide a linear increase in the speed compared to the javascript implementation

Test is a file for demonstrating the use, the values in that test file are all in mainland China which is not a hotspot for businesses, so they should be close to 0

The input file specification is 5 columns: "city","provence","time","latitude","longitude" DELIMITER\_FOR\_NEXT\_ROW

There are no quotation marks in the input file.

The output file specification is 6 columns: "city","provence","time","latitude","longitude","zscore" DELIMITER\_FOR\_NEXT\_ROW

Sources used for this project:
http://resources.esri.com/help/9.3/arcgisengine/java/gp\_toolref/spatial\_statistics\_tools/how\_hot\_spot\_analysis\_colon\_getis\_ord\_gi\_star\_spatial\_statistics\_works.htm
