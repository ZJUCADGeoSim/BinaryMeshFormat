#include <Eigen/Eigen>
#include <doctest/doctest.h>
#include <random>
#include <sstream>

#include <zjucad/bmf/bmf.hpp>

TEST_CASE("test equality") {
    Eigen::MatrixX<zjucad::FLOAT> V(100, 3), TC(100, 3);
    Eigen::MatrixXi F(300, 3), FTC(300, 3);
    V.setRandom();
    TC.setRandom();

    std::mt19937 gen;
    std::uniform_int_distribution<> dis(0, 100);
    auto uni = [&]() { return dis(gen); };

    F = Eigen::MatrixXi::NullaryExpr(100, 3, uni);
    FTC = Eigen::MatrixXi::NullaryExpr(100, 3, uni);

    std::stringstream ss;

    zjucad::write_bmf(ss, V, TC, F, FTC);

    Eigen::MatrixX<zjucad::FLOAT> V2, TC2;
    Eigen::MatrixXi F2, FTC2;

    ss.seekg(0, std::ios::beg);
    zjucad::read_bmf(ss, V2, TC2, F2, FTC2);

    CHECK(V.isApprox(V2));
    CHECK(TC.isApprox(TC2));
    CHECK(F == F2);
    CHECK(FTC == FTC2);
}