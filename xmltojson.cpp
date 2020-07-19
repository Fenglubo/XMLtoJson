#include<stdafx.h>
#define XMLMAP "./Demo-01.xml"

using namespace std;

int main() {
	TiXmlDocument xmldoc;
	Json::Value root;
	if (!xmldoc.LoadFile(XMLMAP)) {
		cout << "打开地图文件失败" << endl;
		return 0;
	}
	TiXmlElement* xmlroot = xmldoc.RootElement();
	double x;
	for (TiXmlElement* point = xmlroot->FirstChildElement("point"); point; point = point->NextSiblingElement("point")) {
		Json::Value temp;
		temp["pointID"] = point->Attribute("name");
		point->Attribute("xPosition", &x);
		temp["pos_x"] = x;
		point->Attribute("yPosition", &x);
		temp["pos_y"] = x;
		root.append(temp);
	}
	for (TiXmlElement* path = xmlroot->FirstChildElement("path"); path; path = path->NextSiblingElement("path")) {
		Json::Value temp;
		path->Attribute("length", &x);
		temp["length"] = x;
		for (int i = 0; i < root.size(); i++)
		{
			if (root[i]["pointID"] == path->Attribute("sourcePoint")) {
				temp["pointID"] = path->Attribute("destinationPoint");
				root[i]["linkPoint"].append(temp);
			}
			else if (root[i]["pointID"] == path->Attribute("destinationPoint")) {
				temp["pointID"] = path->Attribute("sourcePoint");
				root[i]["linkPoint"].append(temp);
			}
		}
	}
	//保存拓扑图
	ofstream ofs;
	ofs.open("./test1.json");
	ofs << root.toStyledString();
	ofs.close();
	return 0;
}