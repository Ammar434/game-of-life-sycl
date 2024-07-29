#pragma once
#include <sycl/sycl.hpp>

const int m_width = 1920;
const int m_height = 1080;
const float ra = 21;
const float ri = ra / 3.0;
const float ri_sq = ri * ri;
const float ra_sq = ra * ra;
const float alpha_n = 0.028;
const float alpha_m = 0.147;
const float b1 = 0.254;
const float b2 = 0.312;
const float d1 = 0.340;
const float d2 = 0.518;
const float dt = 0.05;
// const int begining_array = 130;
const int begining_array =
    static_cast<int>(m_width * m_height / std::pow(ra * 5, 2));
// const int m_width = 3840;
// const int m_height = 2160;
// const float ra = 21;
// const float ri = ra / 3.0;
// const float ri_sq = ri * ri;
// const float ra_sq = ra * ra;
// const float alpha_n = 0.028;
// const float alpha_m = 0.147;
// const float b1 = 0.257;
// const float b2 = 0.312;
// const float d1 = 0.340;
// const float d2 = 0.549;
// const float dt = 0.05;

using type_t = float;
