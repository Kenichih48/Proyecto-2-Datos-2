#ifndef GENETICPUZZLE_XMLPARSER_H
#define GENETICPUZZLE_XMLPARSER_H
#include "tinyxml.h"
#include <SFML/Graphics.hpp>

class XmlParser{
public:
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
    void buildGenerationXml (int generation_, int generationRows, int generationCols)
    {
        TiXmlElement* generation = new TiXmlElement("Generation");

        generation->SetAttribute("generationNumber", to_string(generation_));
        generation->SetAttribute("generationRows", to_string(generationRows));
        generation->SetAttribute("generationCols", to_string(generationCols));

        doc.LinkEndChild(decl);
        doc.LinkEndChild(generation);
    }
    void buildPieceXml(int piece_, int positionX, int positionY, int puzzlePiece)
    {
        TiXmlElement* piece = new TiXmlElement("Piece" + to_string(piece_));

        piece->SetAttribute("positionInMatrix", "(" + to_string(positionX) + "," + to_string(positionY) + ")");
        piece->SetAttribute("solvedPuzzlePieceNumber", puzzlePiece);

        doc.LastChild()->LinkEndChild(piece);
    }
    void saveXml(int generation_)
    {
        doc.SaveFile("Generation" + to_string(generation_) + ".xml");
    }
};

#endif //GENETICPUZZLE_XMLPARSER_H
