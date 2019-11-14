#include "main.h"
#include "geodesic.h"
#include <stdio.h>

#if defined(_MSC_VER)
/* Squelch warnings about scanf */
#  pragma warning (disable: 4996)
#endif

typedef struct {
  double range;
  double bearing;
} RangeBearing;

typedef struct {
  double latitude;
  double longitude;
} LatLon;


DLL_EXPORT void get_gear_lat_lon(int num_rows, double **data, double gear_lat, double gear_lon, double **gear_coords) {
  double a = 6378137, f = 1/298.257223563; /* WGS84 */
  struct geod_geodesic g;
  geod_init(&g, a, f);

  int lat_col = 0;
  int lon_col = 1;
  int bearing_col = 2;
  int range_col = 2;

  double vessel_azimuth, range, gear_azimuth, new_gear_azimuth;
  double lat2, lon2;

  //double **gear_coords[num_rows][2];
//  double **gear_coords = malloc(num_rows * sizeof(**gear_coords));
//  LatLon *gear_coords = malloc(num_rows * sizeof(LatLon));

  for (int i=0; i<num_rows; i++) {
    geod_inverse(&g, data[i][lat_col], data[i][lon_col], gear_lat, gear_lon, &range, &vessel_azimuth, &gear_azimuth);
    geod_direct(&g, data[i][lat_col], data[i][lon_col], vessel_azimuth, data[i][range_col], &lat2, &lon2, &new_gear_azimuth);

    gear_coords[i][lat_col] = lat2;
    gear_coords[i][lon_col] = lon2;
    gear_coords[i][bearing_col] = new_gear_azimuth;

//    if (i < 3) {
//      printf("Vessel Lat/Lon: %f, %f >>> Bearing/Range: %f, %f >>> Gear Lat/Lon: %f, %f\n", data[i][lat_col], data[i][lon_col], bearing, data[i][range_col], gear_coords[i][0], gear_coords[i][1]);
//    }

    gear_lat = lat2;
    gear_lon = lon2;
  }

//  return gear_coords;

};


DLL_EXPORT LatLon *get_lat_lon(double lat1, double lon1, double range, double bearing) {
  double a = 6378137, f = 1/298.257223563; /* WGS84 */
  double lat2, lon2, azi2;
  struct geod_geodesic g;

  geod_init(&g, a, f);
  geod_direct(&g, lat1, lon1, bearing, range, &lat2, &lon2, &azi2);

  // Create a new instance of the LatLon structure
  LatLon *ll = malloc(sizeof (LatLon));
  ll->latitude = lat2;
  ll->longitude = lon2;

  // Return the populated data struct
  return ll;

};

DLL_EXPORT RangeBearing *get_range_bearing(double lat1, double lon1, double lat2, double lon2) {
  double a = 6378137, f = 1/298.257223563; /* WGS84 */
  double azi1, azi2, s12;
  struct geod_geodesic g;

  geod_init(&g, a, f);
  geod_inverse(&g, lat1, lon1, lat2, lon2, &s12, &azi1, &azi2);

  RangeBearing *rb = malloc(sizeof (RangeBearing));
  rb->range = s12;
  rb->bearing = azi1;
  return rb;
};

DLL_EXPORT double sum_test(double a, double b) {
  return a + b;
};


