/*
 * $Revision: 675 $ $Date: 2012-05-22 17:17:55 -0700 (Tue, 22 May 2012) $
 *
 * Copyright by Astos Solutions GmbH, Germany
 *
 * this file is published under the Astos Solutions Free Public License
 * For details on copyright and terms of use see 
 * http://www.astos.de/Astos_Solutions_Free_Public_License.html
 */

#ifndef _VESTA_TEXTURE_FONT_H_
#define _VESTA_TEXTURE_FONT_H_

#include "Object.h"
#include "TextureMap.h"
#include "OGLHeaders.h"
#include <Eigen/Core>
#include <string>
#include <vector>


namespace vesta
{

class DataChunk;
class VertexBuffer;

class TextureFont : public Object
{
public:
    struct Glyph
    {
        unsigned int characterId;
        Eigen::Vector2f textureCoords[4];

        Eigen::Vector2f offset;
        Eigen::Vector2f size;

        float advance;
    };

    enum Encoding
    {
        Ascii,
        Latin1,
        Utf8
    };

    TextureFont();
    ~TextureFont();

    Eigen::Vector2f render(const std::string& text,
                           const Eigen::Vector2f& startPosition) const;
    Eigen::Vector2f renderUtf8(const std::string& text,
                               const Eigen::Vector2f& startPosition) const;
    Eigen::Vector2f renderEncodedString(const std::string& text,
                                        const Eigen::Vector2f& startPosition,
                                        Encoding encoding) const;
    Eigen::Vector2f renderStringToBuffer(const std::string& text,
                                         const Eigen::Vector2f& startPosition,
                                         Encoding encoding,
                                         char* vertexData = NULL,
                                         unsigned int vertexDataSize = 0,
                                         unsigned int* vertexCount = NULL) const;


    float textWidth(const std::string& text) const;
    float textAscent(const std::string& text) const;
    float maxAscent() const;
    float maxDescent() const;
    const Glyph* lookupGlyph(wchar_t ch) const;

    void addGlyph(const Glyph& glyph);
    void buildCharacterSet();
    bool buildFontTexture(unsigned int width,
                          unsigned int height,
                          unsigned char* pixels);

    void bind() const;
    TextureMap* glyphTexture() const
    {
        return m_glyphTexture.ptr();
    }

    bool loadTxf(const DataChunk* data);

    static TextureFont* LoadTxf(const DataChunk* data);
    static TextureFont* GetDefaultFont();

private:
    Eigen::Vector2f renderLatin1ToBuffer(const std::string& text,
                                         const Eigen::Vector2f& startPosition,
                                         char* vertexData,
                                         unsigned int vertexDataSize,
                                         unsigned int* vertexCount) const;
    Eigen::Vector2f renderUtf8ToBuffer(const std::string& text,
                                       const Eigen::Vector2f& startPosition,
                                       char* vertexData,
                                       unsigned int vertexDataSize,
                                       unsigned int* vertexCount) const;

private:
    counted_ptr<TextureMap> m_glyphTexture;
    std::vector<Glyph> m_glyphs;
    std::vector<unsigned int> m_characterSet;
    unsigned int m_maxCharacterId;

    static counted_ptr<TextureFont> ms_defaultFont;

    float m_maxAscent;
    float m_maxDescent;
};

}

#endif // _VESTA_TEXTURE_FONT_H_

