#include "lsystem.hpp"

#include <Magick++.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

std::string LSystem::produce() {
    std::string output = this->axiom;
    std::cout << "n = " << 0 << " : " << output << std::endl;

    for (int n = 1; n < this->recursions + 1; n++) {
        std::string tmp_output = "";
        for (auto cursor_char : output) {
            std::string cursor_str{cursor_char};
            if (std::find(this->constants.begin(), this->constants.end(), cursor_str) != this->constants.end()) {
                tmp_output += cursor_str;
            } else {
                tmp_output += this->rules.at(cursor_str);
            }
        }

        std::cout << "n = " << n << " : " << tmp_output << std::endl;
        output = tmp_output;
    }

    return output;
}

std::pair<int, int> LSystem::get_dimensions() {
    
}

void LSystem::draw() {
    int width = 800;
    int height = 800;

    Magick::Image image(Magick::Geometry(width, height), Magick::Color("white"));
    std::vector<Magick::Drawable> draw_vector;

    image.strokeColor("#00ff00");  // Outline color
    image.strokeWidth(1.3);

    int x_offset = width / 2;
    int y_offset = height;

    for (auto line : this->lines) {
        draw_vector.push_back(Magick::DrawableLine(
            line.first.x + x_offset, line.first.y + y_offset, 
            line.second.x + x_offset, line.second.y + y_offset));
    }

    for (auto drawable : draw_vector) {
        image.draw(drawable);
    }

    image.display();
}