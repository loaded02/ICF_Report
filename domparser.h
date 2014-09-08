#ifndef DOMPARSER_H
#define DOMPARSER_H

/*
* Parses XML Document with 2 hierarchy steps
* and puts them into an QVector. Used for Person class.
*/

#include <QVector>
#include <QDomDocument>
#include <QFile>
#include <iostream>

template< typename T >
class DomParser
{
public:
    DomParser(QVector<T>* daten);

    bool readFile(const QString &fileName);

private:
    void parseRootElement(const QDomElement &element);
    void parseFirstChild(const QDomElement &element,
                           T* parent);
    void parseSecondChild(const QDomElement &element,
                          T* parent);
    QVector<T>* daten;
};

template< typename T >
DomParser<T>::DomParser(QVector<T>* daten)
    :daten(daten){

}

template< typename T >
bool DomParser<T>::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine,
                        &errorColumn)) {
        std::cerr << "Error: Parse error at line " << errorLine << ", "
                  << "column " << errorColumn << ": "
                  << qPrintable(errorStr) << std::endl;
        return false;
    }

    QDomElement root = doc.documentElement();
//    if (root.tagName() != "bookindex") {
//        std::cerr << "Error: Not a bookindex file" << std::endl;
//        return false;
//    }

    parseRootElement(root);
    return true;
}

#endif // DOMPARSER_H
