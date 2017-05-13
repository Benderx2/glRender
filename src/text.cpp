// PLEASE NOTE: THIS IMPLEMENTATION WAS TAKEN FROM R3X VIRTUAL MACHINE. IT IS OLD CODE THAT WILL BE REPLACED IN THE NEAR
// FUTURE WITH A BETTER TEXT RENDERER. (PREFERABLY FREETYPE)
#include <iostream>
#include <text.h>
#include <stb_image.h>

TextRender::TextRender(const std::string& font) {
    int height, width, n_comp;
    unsigned char* image_data = stbi_load(font.c_str(), &width, &height, &n_comp, STBI_rgb_alpha);
    if(image_data == NULL) {
      std::cout << "Failed to load image for given font: " << font << std::endl;
    } else {
      std::cout << "Loading font data from: '" << font << "'" << std::endl;
    }
    uint32_t* pixels = (uint32_t*)image_data;
    float glyph_x[256][4];
    box_w = width/16.0f;
    box_h = height/16.0f;
    int first_x, last_x;
    bool empty;

    for(int bx = 0; bx < 16; bx++)
    {
        for(int by = 0; by < 16; by++)
        {
            first_x = last_x = 0;
            empty = true;
            for(int x = 0; x < box_w; x++)
            {
                for(int y = 0; y < box_h; y++)
                {
                    if(pixels[(y + by * box_h) * 16 * box_w+(x + bx * box_w)] == 0x00FF00FF || pixels[(y + by * box_h) * 16 * box_w + (x + bx * box_w)] == 0x0000FF00)
                    {
                        pixels[(y + by * box_h) * 16 * box_w + (x + bx * box_w)] = 0xFF000000;
                    }
                    else
                    {
                        if(first_x == 0)
                            first_x = x;
                        if(last_x < x)
                            last_x = x;
                        empty = false;
                    }
                }
            }
            if(empty)
              last_x = box_w/8.0f;
              glyph_x[by * 16 + bx][0] = bx * box_w + first_x;
              glyph_x[by * 16 + bx][1] = by * box_h;
              glyph_x[by * 16 + bx][2] = bx * box_w + last_x + 1;
              glyph_x[by * 16 + bx][3] = (by + 1) * box_h;
              w[by *16 + bx] = last_x - first_x + 1;
        }
    }

    glGenTextures(1, &(tex));

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    display_list = glGenLists(256);
    mat_list = glGenLists(2);

    float iw = width, ih = height;

    for(int i = 0; i < 256; i++)
    {
        glNewList(display_list+i, GL_COMPILE);

        glBegin(GL_QUADS);

        glTexCoord2f(glyph_x[i][2]/iw, glyph_x[i][1]/ih);
        glVertex2f(w[i], 0);

        glTexCoord2f(glyph_x[i][0]/iw, glyph_x[i][1]/ih);
        glVertex2f(0, 0);

        glTexCoord2f(glyph_x[i][0]/iw, glyph_x[i][3]/ih);
        glVertex2f(0, box_h);

        glTexCoord2f(glyph_x[i][2]/iw, glyph_x[i][3]/ih);
        glVertex2f(w[i], box_h);

        glEnd();

        glTranslatef(w[i]+1, 0.0, 0.0 );

        glEndList();
    }

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glNewList(mat_list, GL_COMPILE);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, viewport[2], viewport[3], 0.0f, 1.0f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glEndList();

    glNewList(mat_list+1, GL_COMPILE);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEndList();

    stbi_image_free(image_data);
}

void TextRender::Render(const std::string& str, int x, int y, float scale) {
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex);

  glCallList(mat_list);

  glTranslatef(x, y, -2.0f);
  glScalef(scale, scale, scale);
  glListBase(display_list);
  glCallLists(str.length(), GL_UNSIGNED_BYTE, str.c_str());

  glCallList(mat_list+1);

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

  glPopAttrib();
}
