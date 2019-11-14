#ifndef PYGEOGRAPHICLIB_H_INCLUDED
#define PYGEOGRAPHICLIB_H_INCLUDED

#define DLL_EXPORT __declspec(dllexport)

DLL_EXPORT void get_gear_lat_lon(int num_rows, double **data, double gear_lat, double gear_lon, double **gear_coords)
DLL_EXPORT RangeBearing *get_range_bearing(double lat1, double lon1, double lat2, double lon2);
DLL_EXPORT LatLon *get_lat_lon(double lat1, double lon1, double range, double bearing);
DLL_EXPORT double sum_test(double a, double b)

#endif // PYGEOGRAPHICLIB_H_INCLUDED

