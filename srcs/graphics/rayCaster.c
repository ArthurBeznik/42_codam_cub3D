#include <graphics.h>

void	rayCasting(t_general_data *data)
{
	int		i;
	double	rayAngle;
	int		dof;
	int		rayX;
	int		rayY;
	int		yOffset;
	int		xOffset;

	i = 0;
	rayAngle = data->file_data->player->angle;
	fprintf(stderr, "TESTING\n");
	while (i < 1)
	{
		fprintf(stderr, "TESTING1\n");
		dof = 0;
		float aTan = -1 / tan(rayAngle);
		if (rayAngle > PI)
		{
			fprintf(stderr, "TESTING2\n");
			rayY = (((int)data->file_data->player->y >> 6) << 6) - 0.0001;
			rayX = (data->file_data->player->y - rayY) * aTan + data->file_data->player->x;
			yOffset = -64;
			xOffset = -yOffset * aTan;
		}
		if (rayAngle < PI)
		{
			fprintf(stderr, "TESTING3\n");
			rayY = (((int)data->file_data->player->y >> 6) << 6) + 64;
			rayX = (data->file_data->player->y - rayY) * aTan + data->file_data->player->x;
			yOffset = 64;
			xOffset = -yOffset * aTan;
		}
		if (rayAngle == 0 || rayAngle == PI)
		{
			fprintf(stderr, "TESTING4\n");
			rayX = data->file_data->player->x;
			rayY = data->file_data->player->y;
			dof = 8;
		}
		while (dof < 8)
		{
			fprintf(stderr, "TESTING5\n");
			int mapX = (int)(rayX) >> 6;
			fprintf(stderr, "mapX: %d\n", mapX);
			int mapY = (int)(rayY) >> 6;
			fprintf(stderr, "mapY: %d\n", mapY);
			int mapPosition = mapY * data->file_data->map_data->col + mapX;
			fprintf(stderr, "mapPosition: %d\n", mapPosition);
			fprintf(stderr, "mapData: %s\n", data->file_data->map_data->copy[mapPosition]);
			if (mapPosition < mapX * mapY && data->file_data->map_data->copy[mapY][mapX] == '1')
			{
				fprintf(stderr, "TESTING6\n");
				dof = 8;
			}
			else
			{
				fprintf(stderr, "TESTING7\n");
				rayX += xOffset;
				rayY += yOffset;
				dof += 1;
			}
		}
		i++;
	}
}
