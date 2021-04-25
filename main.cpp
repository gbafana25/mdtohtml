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



string process_line(string line) {
		if(line.substr(0, 1) == "#") {
			if(line.substr(0, 2) == "##") {
				if(line.substr(0, 3) == "###") {
					line.erase(0, 3);
					line.insert(0, "<h3>");
					line.append("</h3>");
				} else {
					line.erase(0, 2);
					line.insert(0, "<h2>");
					line.append("</h2>");

				}
			} else {
				line.erase(line.begin());
				line.insert(0, "<h1>");
				line.append("</h1>");
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
			if(line.find("**") != string::npos) {
				int fa = line.find("**");
				for(int i = fa+1; i < line.size(); i++) {
					if(line.substr(i, 2) == "**") {
						string bold = line.substr(fa+2, (i-2)-fa);
						cout << bold << endl;
						bold.insert(0, "<b>");
						bold.append("</b>");
						line.erase(fa, i+1);
						line.insert(fa, bold);
						break;
					}	
				}
			}
				
		}


	line.append("\n");
	return line;

}


int main() {
	fstream testfile;
	fstream outfile;
	testfile.open("/home/gareth/table-signal/README.md", ios::in);
	
	string line;
	string parsed;
	while(getline(testfile, line)) {
		parsed.append(process_line(line));
	
	}

	cout << parsed;
	outfile.open("test.html", ios::out);
	outfile << parsed;

}
