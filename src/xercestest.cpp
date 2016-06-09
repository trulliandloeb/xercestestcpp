//============================================================================
// Name        : xercestest.cpp
// Author      : trulliandloeb
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	try {
		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n" << message << "\n";
		XMLString::release(&message);
		return 1;
	}

	XMLCh tempStr[100];
	XMLString::transcode("LS", tempStr, 99);
	DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(
			tempStr);
	DOMLSParser* parser = ((DOMImplementationLS*) impl)->createLSParser(
			DOMImplementationLS::MODE_SYNCHRONOUS, 0);

	// optionally you can set some features on this builder
	if (parser->getDomConfig()->canSetParameter(XMLUni::fgDOMValidate, true))
		parser->getDomConfig()->setParameter(XMLUni::fgDOMValidate, true);
	if (parser->getDomConfig()->canSetParameter(XMLUni::fgDOMNamespaces, true))
		parser->getDomConfig()->setParameter(XMLUni::fgDOMNamespaces, true);
	if (parser->getDomConfig()->canSetParameter(
			XMLUni::fgDOMDatatypeNormalization, true))
		parser->getDomConfig()->setParameter(XMLUni::fgDOMDatatypeNormalization,
				true);

	// optionally you can implement your DOMErrorHandler (e.g. MyDOMErrorHandler)
	// and set it to the builder
//	MyDOMErrorHandler* errHandler = new myDOMErrorHandler();
//	parser->getDomConfig()->setParameter(XMLUni::fgDOMErrorHandler, errHandler);

	char* xmlFile = "/home/tlcore/src/xerces/x1.xml";
	DOMDocument *doc = 0;

	try {
		doc = parser->parseURI(xmlFile);
		cout << doc->getDoctype() << endl;
		cout << XMLString::transcode(doc->getXmlEncoding()) << endl;
		cout << doc->getNodeType() << endl;
		DOMElement* root = doc->getDocumentElement();
		cout << XMLString::transcode(root->getNodeName()) << endl;
		cout << root->getNodeType() << endl;
		cout << XMLString::transcode(root->getLocalName()) << endl;
		cout << root->getPrefix() << endl;
		string prefix;
		if (root->getPrefix() != 0)
		{
			char* temp = XMLString::transcode(root->getPrefix());
			prefix = temp;
			XMLString::release(&temp);
		}
		cout << prefix << endl;
		cout << "========" << endl;
		cout << XMLString::transcode(root->getNamespaceURI()) << endl;
		 DOMNodeList* list = doc->getElementsByTagNameNS(root->getNamespaceURI(), XMLString::transcode("Name"));
		 cout << XMLString::transcode(list->item(0)->getNodeName()) << endl;

	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return -1;
	} catch (const DOMException& toCatch) {
		char* message = XMLString::transcode(toCatch.msg);
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		return -1;
	} catch (...) {
		cout << "Unexpected Exception \n";
		return -1;
	}

	parser->release();
//	delete errHandler;
	return 0;
}
