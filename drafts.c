
int find_closest_vert(t_scene *scene, t_player *p)
{
	double	dist_to_next_vert_intersect;
	int		dist_to_next_vert_x;

	printf("\nVERT:\n");
	
	p->next_vert_x = ((int)(p->x / SEGM) + p->x_dir) * SEGM;
	// printf("next_vert_x %d\n", p->next_vert_x);
	dist_to_next_vert_x = fabs(p->x - p->next_vert_x);
	// printf("dist_to_next_vert_x %d\n", dist_to_next_vert_x);
	dist_to_next_vert_intersect = fabs(dist_to_next_vert_x / cos(p->angle));
	// printf("dist_to_next_vert_intersect %f\n", dist_to_next_vert_intersect );
	p->next_vert_y = (int)(dist_to_next_vert_intersect * sin(p->angle) * -1 +(p->y));
	// printf("next_vert_y %d\n", p->next_vert_y);
	return (dist_to_next_vert_intersect);
}


int find_closest_hor(t_scene *scene, t_player *p)
{
	double	dist_to_next_hor_intersect;
	int		dist_to_next_hor_y;
	int		y_dir;
	
	// y_dir = p->y_dir;
	printf("\nHOR:\n");

	p->next_hor_y = ((int)(p->y / SEGM + p->y_dir)) * SEGM; 
	printf("next_hor_y %d\n", p->next_hor_y );
	dist_to_next_hor_y = fabs(p->y - p->next_hor_y);
	printf("dist_to_next_hor_y %d\n", dist_to_next_hor_y);
	dist_to_next_hor_intersect = fabs(dist_to_next_hor_y / cos(p->angle + PI / 2));
	printf("dist_to_next_hor_intersect %f\n", dist_to_next_hor_intersect );
	p->next_hor_x = (int)(dist_to_next_hor_intersect * sin(p->angle + PI / 2) + (p->x) );
	printf("next_hor_x %d\n", p->next_hor_x );

	return (dist_to_next_hor_intersect);
}

отдельоно просчитать пути до
- верт стенной преграды
- гор стенной преграды

while segm != WAll 
	dist to vert += calculate_segment of the path inside the square ()

	// printf("P y: %d, x: %d\n", p->y, p->x);
	// printf("a %f\n", p->angle);
	// printf("dir: y_dir %d, x_dir %d\n", p->y_dir, p->x_dir);


void calc_ray(t_scene *scene)
{
	t_player	*p;
	t_ray		*ray;
	char	*cv = "check VERT";
	char	*ch = "chevk HOR";

	ray = malloc(sizeof(t_ray));
	if (ray)
		scene->ray = ray;
	p = scene->p;
	update_dir(scene, p);
	printf("x_dir %d, y_dir %d\n", p->x_dir, p->y_dir);
	ray->next_hor_x = p->x;
	ray->next_hor_y = p->y;
	ray->next_vert_x = p->x;
	ray->next_vert_y = p->y;

	ray->vert_dist = find_next_vert(scene, ray, p->x, p->y); 
	ray->hor_dist = find_next_hor(scene, ray, p->x, p->y);

	while (is_inside_map(scene, ray->next_vert_x, ray->next_vert_y) &&
		not_wall(scene, ray->next_vert_x, ray->next_vert_y, cv))
		{
			// printf("PREV  DIST to VERT %d   ", ray->vert_dist);
				ray->vert_dist += find_next_vert(scene, ray, ray->next_vert_x, ray->next_vert_y);
			// printf("N E W  DIST TO VERT %d   ", ray->vert_dist);
			// printf("||||||||||||||\n", ray->vert_dist);
		}
	while (is_inside_map(scene, ray->next_hor_x, ray->next_hor_y) &&
		not_wall(scene, ray->next_hor_x, ray->next_hor_y, ch))
		{
			// printf("PREV  DIST to HORRRRRRRRRR %d   ", ray->hor_dist);
				ray->hor_dist += find_next_hor(scene, ray, ray->next_hor_x, ray->next_hor_y);
			// printf("N E W  DIST to HORRRRRRRRRR %d   ", ray->hor_dist);
			// printf("==============%d\n", ray->vert_dist);

		}

	if (ray->vert_dist < ray->hor_dist)
		draww_point(scene, ray->next_vert_y, ray->next_vert_x);
	else
		draww_point(scene, ray->next_hor_y, ray->next_hor_x);

	//while 
}


int not_wall(t_scene *scene, int x, int y, char *str)
{
	t_player	*p;
    int         add_x;
    int         add_y;

	p = scene->p;
    if (p->x_dir == -1)
        add_x = -1;
    else
        add_x = 0;

	printf("            p->y_dir %d\n", p->y_dir);
    	printf("            p->x_dir %d\n", p->x_dir);
	if(scene->map[y / SEGM][x / SEGM + add_x] != WALL) //  + p->y_dir +
	{
        printf("|%s|: i thing y%d and x%d ARE NOT A WALL\n", str, y / SEGM  + add_y , x / SEGM + add_x);

    	return(1);
    }
    else
    {
        printf("|%s|: i thing y%d and x%d is wall\n", str, y / SEGM  + add_y , x / SEGM  + add_x);

	    return (0);
    }
}

	printf("ray->vert_dist %d\n", ray->vert_dist);
	printf("ray->hor_dist %d\n", ray->hor_dist);
