#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>

#include <zjucad/bmf/bmf.hpp>

int main(int argc, char *arg[]) {
    if (argc != 4) {
        std::cerr << "usage: " << arg[0] << " <o2b|b2o> input output" << std::endl;
        return 1;
    }
    std::string mode = arg[1];
    char *input = arg[2];
    char *output = arg[3];
    Eigen::MatrixX<zjucad::FLOAT> CN, V, TC;
    Eigen::MatrixXi FN;
    Eigen::MatrixXi F;
    Eigen::MatrixXi FTC;

    if (mode == "o2b") {
        igl::readOBJ(input, V, TC, CN, F, FTC, FN);
        zjucad::write_bmf(output, V, TC, F, FTC);
    } else if (mode == "b2o") {
        zjucad::read_bmf(input, V, TC, F, FTC);
        igl::writeOBJ(output, V, F, CN, FN, TC, FTC);
    } else {
        std::cerr << "unknown mode: " << mode << std::endl;
        return 1;
    }
    return 0;
}