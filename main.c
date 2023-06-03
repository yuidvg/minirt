#include <mlx.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct
{
	double x;
	double y;
	double z;
} Vector3;

typedef struct
{
	Vector3 position;
	double radius;
	int color;
} Sphere;

typedef struct
{
	Vector3 position;
	Vector3 normal;
	int color;
} Plane;

typedef struct
{
	Sphere sphere;
	Vector3 light;
	Plane plane;
} Scene;

// ベクトルの計算関数

Vector3 add_vectors(Vector3 v1, Vector3 v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 scale_vector(Vector3 v, double scalar)
{
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

double dot_product(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 subtract_vectors(Vector3 v1, Vector3 v2)
{
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 normalize(Vector3 v)
{
	double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	Vector3 result;
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return result;
}

double clamp(double value, double min, double max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

void render_scene(Scene scene, void *mlx, void *window)
{
	int x, y;

	Vector3 camera_position = (Vector3){0, -2, 0};

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			double ray_dir_x = (x - WIDTH / 2) / (WIDTH / 2.0);
			double ray_dir_y = -(y - HEIGHT / 2) / (HEIGHT / 2.0);
			double ray_dir_z = 1.0;

			Vector3 ray_direction = normalize((Vector3){ray_dir_x, ray_dir_y, ray_dir_z});

			Vector3 ray_origin = camera_position;
			Vector3 sphere_to_ray = subtract_vectors(ray_origin, scene.sphere.position);

			double a = dot_product(ray_direction, ray_direction);
			double b = 2 * dot_product(ray_direction, sphere_to_ray);
			double c = dot_product(sphere_to_ray, sphere_to_ray) - scene.sphere.radius * scene.sphere.radius;

			double discriminant = b * b - 4 * a * c;

			if (discriminant >= 0)
			{
				double t = (-b - sqrt(discriminant)) / (2 * a);
				Vector3 intersection_point = {
					ray_origin.x + ray_direction.x * t,
					ray_origin.y + ray_direction.y * t,
					ray_origin.z + ray_direction.z * t};

				Vector3 normal = normalize(subtract_vectors(intersection_point, scene.sphere.position));

				Vector3 light_direction = normalize(subtract_vectors(scene.light, intersection_point));
				double diffuse_intensity = dot_product(normal, light_direction);
				diffuse_intensity = clamp(diffuse_intensity, 0.0, 1.0);

				// 影の計算
				Vector3 shadow_ray_origin = add_vectors(intersection_point, scale_vector(normal, 0.001));

				Vector3 shadow_ray_direction = subtract_vectors(scene.light, shadow_ray_origin);
				double shadow_t = dot_product(normalize(scene.plane.normal), subtract_vectors(scene.plane.position, shadow_ray_origin)) / dot_product(normalize(scene.plane.normal), shadow_ray_direction);

				if (shadow_t > 0 && shadow_t < 1)
				{
					// 光源からの光が球によって遮られている場合は床に黒の影を設定
					mlx_pixel_put(mlx, window, x, y, 0x000000);
					continue;
				}

				double ambient = 0.1;
				double diffuse = diffuse_intensity;
				int r = (scene.sphere.color >> 16) & 0xFF;
				int g = (scene.sphere.color >> 8) & 0xFF;
				int b = scene.sphere.color & 0xFF;
				int shade_r = (int)(ambient * r + diffuse * r);
				int shade_g = (int)(ambient * g + diffuse * g);
				int shade_b = (int)(ambient * b + diffuse * b);

				shade_r = (shade_r > 255) ? 255 : shade_r;
				shade_g = (shade_g > 255) ? 255 : shade_g;
				shade_b = (shade_b > 255) ? 255 : shade_b;

				int color = (shade_r << 16) | (shade_g << 8) | shade_b;
				mlx_pixel_put(mlx, window, x, y, color);
			}
			else
			{
				Vector3 plane_to_ray = subtract_vectors(ray_origin, scene.plane.position);
				double denominator = dot_product(scene.plane.normal, ray_direction);
				if (denominator != 0)
				{
					double t = dot_product(scene.plane.normal, plane_to_ray) / denominator;
					if (t >= 0)
					{
						Vector3 intersection_point = {
							ray_origin.x + ray_direction.x * t,
							ray_origin.y + ray_direction.y * t,
							ray_origin.z + ray_direction.z * t};

						Vector3 plane_normal = scene.plane.normal;
						double intersection_dot_normal = dot_product(ray_direction, plane_normal);
						if (intersection_dot_normal <= 0)
						{
							// 床に当たった場合、影の判定
							Vector3 shadow_ray_origin = add_vectors(intersection_point, scale_vector(plane_normal, 0.001));

							Vector3 shadow_ray_direction = subtract_vectors(scene.light, shadow_ray_origin);
							double shadow_t = dot_product(normalize(scene.plane.normal), subtract_vectors(scene.plane.position, shadow_ray_origin)) / dot_product(normalize(scene.plane.normal), shadow_ray_direction);

							if (shadow_t > 0 && shadow_t < 1)
							{
								// 光源からの光が遮られている場合は床に黒の影を設定
								mlx_pixel_put(mlx, window, x, y, 0x000000);
								continue;
							}

							int color = scene.plane.color;
							mlx_pixel_put(mlx, window, x, y, color);
						}
					}
				}
			}
		}
	}
}

int main(void)
{
	void *mlx;
	void *window;
	Scene scene;

	mlx = mlx_init();
	window = mlx_new_window(mlx, WIDTH, HEIGHT, "Ray Tracing");

	scene.sphere.position = (Vector3){0, -2, -5}; // 球の位置を調整（y座標を-2に設定）
	scene.sphere.radius = 2.0;
	scene.sphere.color = 0x00FF00;

	scene.light = (Vector3){5, -5, -5};

	scene.plane.position = (Vector3){0, 1, -2}; // 地面の位置を調整（y座標を0に設定）
	scene.plane.normal = (Vector3){0, 1, 0};
	scene.plane.color = 0x808080;

	render_scene(scene, mlx, window);

	mlx_loop(mlx);

	return 0;
}
