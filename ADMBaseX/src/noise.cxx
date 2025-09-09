#include <loop.hxx>

#include <cctk.h>
#include <cctk_Arguments.h>
#include <cctk_Parameters.h>

#include <random>

namespace ADMBaseX {
using namespace Loop;
using namespace std;

extern "C" void ADMBaseX_add_noise(CCTK_ARGUMENTS) {
  DECLARE_CCTK_ARGUMENTS_ADMBaseX_add_noise;
  DECLARE_CCTK_PARAMETERS;

  // Hardware random device
  random_device device;
  // Create and seed software random number engine from hardware random number
  default_random_engine engine(device());
  // Random number distribution
  uniform_real_distribution<CCTK_REAL> distribution(-noise_amplitude,
                                                    noise_amplitude);
  const auto add_noise = [&](CCTK_REAL &restrict var) {
    var += distribution(engine);
  };

  const GF3D<CCTK_REAL, 1, 1, 1> gxx_(cctkGH, gxx);
  const GF3D<CCTK_REAL, 1, 1, 1> gxy_(cctkGH, gxy);
  const GF3D<CCTK_REAL, 1, 1, 1> gxz_(cctkGH, gxz);
  const GF3D<CCTK_REAL, 1, 1, 1> gyy_(cctkGH, gyy);
  const GF3D<CCTK_REAL, 1, 1, 1> gyz_(cctkGH, gyz);
  const GF3D<CCTK_REAL, 1, 1, 1> gzz_(cctkGH, gzz);

  const GF3D<CCTK_REAL, 1, 1, 1> kxx_(cctkGH, kxx);
  const GF3D<CCTK_REAL, 1, 1, 1> kxy_(cctkGH, kxy);
  const GF3D<CCTK_REAL, 1, 1, 1> kxz_(cctkGH, kxz);
  const GF3D<CCTK_REAL, 1, 1, 1> kyy_(cctkGH, kyy);
  const GF3D<CCTK_REAL, 1, 1, 1> kyz_(cctkGH, kyz);
  const GF3D<CCTK_REAL, 1, 1, 1> kzz_(cctkGH, kzz);

  const GF3D<CCTK_REAL, 1, 1, 1> alp_(cctkGH, alp);

  const GF3D<CCTK_REAL, 1, 1, 1> dtalp_(cctkGH, dtalp);

  const GF3D<CCTK_REAL, 1, 1, 1> betax_(cctkGH, betax);
  const GF3D<CCTK_REAL, 1, 1, 1> betay_(cctkGH, betay);
  const GF3D<CCTK_REAL, 1, 1, 1> betaz_(cctkGH, betaz);

  const GF3D<CCTK_REAL, 1, 1, 1> dtbetax_(cctkGH, dtbetax);
  const GF3D<CCTK_REAL, 1, 1, 1> dtbetay_(cctkGH, dtbetay);
  const GF3D<CCTK_REAL, 1, 1, 1> dtbetaz_(cctkGH, dtbetaz);

  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(gxx_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(gxy_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(gxz_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(gyy_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(gyz_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(gzz_(p.I)); });

  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(kxx_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(kxy_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(kxz_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(kyy_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(kyz_(p.I)); });
  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(kzz_(p.I)); });

  loop_int<1, 1, 1>(cctkGH, [&](const PointDesc &p) { add_noise(alp_(p.I)); });

  loop_int<1, 1, 1>(cctkGH,
                    [&](const PointDesc &p) { add_noise(dtalp_(p.I)); });

  loop_int<1, 1, 1>(cctkGH,
                    [&](const PointDesc &p) { add_noise(betax_(p.I)); });
  loop_int<1, 1, 1>(cctkGH,
                    [&](const PointDesc &p) { add_noise(betay_(p.I)); });
  loop_int<1, 1, 1>(cctkGH,
                    [&](const PointDesc &p) { add_noise(betaz_(p.I)); });

  loop_int<1, 1, 1>(cctkGH,
                    [&](const PointDesc &p) { add_noise(dtbetax_(p.I)); });
  loop_int<1, 1, 1>(cctkGH,
                    [&](const PointDesc &p) { add_noise(dtbetay_(p.I)); });
  loop_int<1, 1, 1>(cctkGH,
                    [&](const PointDesc &p) { add_noise(dtbetaz_(p.I)); });
}

} // namespace ADMBaseX
