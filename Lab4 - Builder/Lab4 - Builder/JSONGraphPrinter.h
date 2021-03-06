#pragma once

#include "AbstactGraphPrinter.h"
#include <string>

class JSONGraphPrinter : public AbstractGraphPrinter {

private:
	string serialization;
public:
	JSONGraphPrinter();
	~JSONGraphPrinter();
	virtual void print_graph(GraphUML* graph) override;
	virtual void print_header() override;
	virtual void print_classes(vector< ClassUML* > classes) override;
	virtual void print_class(ClassUML* node) override;
	virtual void print_arrows(vector< ArrowUML* > arrows) override;
	virtual void print_arrow(ArrowUML* arrow) override;
	virtual void print_end() override;
	virtual string get_serialization() override;
};

JSONGraphPrinter::JSONGraphPrinter() : serialization("")
{
}

JSONGraphPrinter::~JSONGraphPrinter()
{
}

void JSONGraphPrinter::print_header() {
	serialization += "{\n\t\"graphml\": {";
	serialization += "\t\t\"key\": [\n\t\t\t{\n\t\t\t\t\"_id\": \"at\",\n\t\t\t\t\"_for\" : \"node\",\n\t\t\t\t\"_attr.name\" : \"attribute\",\n\t\t\t\t\"_attr.type\" : \"string\"\n\t\t\t},\n";
	serialization += "\t\t\t{\n\t\t\t\t\"_id\": \"mt\",\n\t\t\t\t\"_for\" : \"node\",\n\t\t\t\t\"_attr.name\" : \"method\",\n\t\t\t\t\"_attr.type\" : \"string\"\n\t\t\t},\n";
	serialization += "\t\t\t{\n\t\t\t\t\"_id\": \"tp\",\n\t\t\t\t\"_for\" : \"edge\",\n\t\t\t\t\"_attr.name\" : \"type\",\n\t\t\t\t\"_attr.type\" : \"string\"\n\t\t\t},\n\t\t],\n";
	serialization += "\t\t\"graph\": {\"\n";
}

void JSONGraphPrinter::print_classes(vector<ClassUML*> classes)
{
	serialization += "\t\t\t\"node\": [\n";
	for (int i = 0; i < classes.size(); i++)
	{
		print_class(classes[i]);
	}
	serialization += "\t\t\t],\n";
}

void JSONGraphPrinter::print_class(ClassUML* node)
{
	serialization += "\t\t\t\t{\n";
	for (int i = 0; i < node->attributes.size(); i++)
	{
		serialization += "\t\t\t\t\t\"data\": {\n";
		serialization += "\t\t\t\t\t\t\"_key\": \"at\",\n";
		serialization += "\t\t\t\t\t\t\"__text\" : \"" + node->attributes[i] + "\"\n";
		serialization += "\t\t\t\t\t},\n";
	}
	for (int i = 0; i < node->operations.size(); i++)
	{
		serialization += "\t\t\t\t\t\"data\": {\n";
		serialization += "\t\t\t\t\t\t\"_key\": \"mt\",\n";
		serialization += "\t\t\t\t\t\t\"__text\" : \"" + node->operations[i] + "\"\n";
		serialization += "\t\t\t\t\t},\n";
	}
	serialization += "\t\t\"_id\": \"" + node->id + "\"\n";


}

void JSONGraphPrinter::print_arrows(vector<ArrowUML*> arrows)
{
	for (int i = 0; i < arrows.size(); i++)
	{
		print_arrow(arrows[i]);
	}
}

void JSONGraphPrinter::print_arrow(ArrowUML* arrow)
{
	serialization += "\t\t<edge id = \"" + arrow->id + "\" source = \" " + arrow->source + "\" target = \"" + arrow->target + "\">\n";
	serialization += "\t\t\t<data key = \"tp\">" + arrow->type + "< / data>\n";
	serialization += "\t\t</edge>\n";
}


void JSONGraphPrinter::print_end() {
	serialization += "\t\t\"_xmlns:xsi\" : \"http://www.w3.org/2001/XMLSchema-instance\",\n";
	serialization += "\t\t\"_xsi:schemaLocation\" : \"http://graphml.graphdrawing.org/xmlns\"\n";
	serialization += "\t\thttp://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\"\n\t}\n}";
}

string JSONGraphPrinter::get_serialization()
{
	return serialization;
}

void JSONGraphPrinter::print_graph(GraphUML* graph) {
	print_header();
	print_classes(graph->getClasses());
	print_arrows(graph->getArrows());
	serialization += "\t\t\t\"_id\": \"" + graph->get_graph_id() + "\",\n\t\t\t\"_edgedefault\" : \"";
	if (graph->get_directed()) {
		serialization += "directed\"\n\t\t},";
	}
	else {
		serialization += "undirected\"\n\t\t},";
	}
	print_end();
}