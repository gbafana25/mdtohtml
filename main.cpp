#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class link {
	public:
		string tag;
		int pos;

};

string getlink(string in) {
	// get hyperlink name
	string lname;
	string raw;
	string full;
	int ob = in.find("[");
	int cb = in.find("]");
	int ol = in.find("(");
	int cl = in.find(")");
	//link url;
	lname = in.substr(ob+1, (cb-1)-ob);
	raw = in.substr(ol+1, (cl-1)-ol);
	raw.insert(0, "'");
	raw.append("'");
	full += "<a href=" + raw + ">" + lname + "</a>";
	//in.append(full);
	in.erase(ob, cl);
	return full;

}

int * getlinklimits(string line) {
	int inds[2];
	inds[0] = line.find("[");
	inds[1] = line.find(")");	

}

bool checklink(string in) {
	int ob = in.find("[");
	int cb = in.find("]");
	int ol = in.find("(");
	int cl = in.find(")");
	if(ob != string::npos || cb != string::npos && ol != string::npos || cl != string::npos && in.substr(ol+1, 5) == "https") {
		return true;

	} else {
		return false;
	}

}

void scan_paragraph(string l) {
	//cout << lnk.tag;

	//return l;
	

}

string process_line(string line) {
	string tag = "<h1>";
	string output = line;
		if(line.substr(0, 1) == "#") {
			if(line.substr(0, 2) == "##") {
				line.erase(0, 2);
				line.insert(0, "<h2>");
				line.append("</h2>");
			} else {
				line.erase(line.begin());
				line.insert(0, tag);
				tag.insert(1, "/");
				line.append(tag);
			}
		} else {
			// insert <p> tags
			line.insert(0, "<p>");
			line.append("</p>");
			if(checklink(line) == true) {
				//line.append(getlink(line));
				int start = line.find("[");
				line.insert(start, getlink(line));
				line.erase(line.find("["), line.find(")"));	
			}
		}


	line.append("\n");
	return line;

}


int main() {
	fstream testfile;
	fstream outfile;
	testfile.open("/home/gareth/esp8266_honeypot/README.md", ios::in);
	
	string line;
	string parsed;
	while(getline(testfile, line)) {
		parsed.append(process_line(line));
	
	}
	cout << parsed;
	outfile.open("test.html", ios::out);
	outfile << parsed;

}
