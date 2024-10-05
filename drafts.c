
void draw_player(t_scene *scene)
{
	t_player	*p;
	int			v_x;
	int			v_y;
	int			y;
	int			x;
	double		angle;
	// let it be in ray structure and this function takes angle and returns x y ray coordinates? (but I calculate intersection )
	p = scene->p;


	v_x = (int)(V * cos(angle) * p->x_dir + p->x);
	// printf("(v_x) %d = %d (V) * %f (cos(%f)) * %d (p->x_dir) + %d (p->x) \n", v_x, V, cos(angle), angle, p->x_dir, p->x);
	v_y = (int)(V * sin(angle) * p->y_dir + p->y);
	// printf("(v_y) %d = %d (V) * %f (sin(%f)) * %d (p->y_dir) + %d (p->y) \n", v_y, V, sin(angle), angle, p->y_dir, p->y);

	x = p->x;
	y = p->y;
	double step_coef;
	if (fabs(v_y - y) < fabs(v_x - x))
		step_coef = fabs(v_y - y) /  fabs(v_x - x);
	else 
		step_coef = fabs(v_x - x) /  fabs(v_y - y);
	printf ("vy - y = %f  /  vx - x = %f\n",  fabs(v_y - y), fabs(v_x - x) );
		printf("coef: %f\n", step_coef);

	printf("P y: %d, x: %d\n", y, x);
	printf("V y: %d, x: %d\n", v_y, v_x);
	printf("angle: %f, x_dir: %d, y_dir: %d\n", p->angle, p->x_dir, p->y_dir);

	mlx_put_pixel(scene->map_img, y, x, PLAYERC, scene);
	
	double bufer = 0;

	// while(fabs(v_y - y) > 0 || fabs(v_x - x) > 0)
	// {
	// 	// sleep(1);
	// 	printf("y: %d, x: %d\n", y, x);
	// 	printf("V y: %d, x: %d\n", v_y, v_x); 

	// 	mlx_put_pixel(scene->map_img, y, x, PLAYERC, scene);
		
	// 	if ((fabs(v_x - x) > 0))
	// 		x = x + p->x_dir;
	// 	bufer +=  step_coef;
	// 	if (step_coef == 0)
	// 		y = y + p->y_dir;
	// 	if (bufer >= 1)
	// 	{
	// 		if (fabs(v_y - y) > 0)
	// 			y = y + p->y_dir;
	// 		bufer--;
	// 	}
	// 	printf("bufer %f\n", bufer);
	// 	printf("coef: %f\n", step_coef);
	// }

}

void find_closest(t_scene *scene, t_player *p)
{
	double	dist_to_next_vert_intersect;
	int		next_vert_y;
	int		next_vert_x;
	int		dist_to_next_vert_x;
	printf("	\n\nangle %2f   (%2f)\n ", p->angle, p->angle * 180 / PI);
	update_dir(scene, p);
	printf("		updated angle %2f   (%2f)\n", p->angle, p->angle * 180 / PI); printf("			X dir %d   Y dir %d \n", p->x_dir, p->y_dir);
	next_vert_x = ((int)(p->x / SEGM) + p->x_dir) * SEGM; 
	printf("				next_vert_x %d\n", next_vert_x);
	dist_to_next_vert_x = fabs(p->x - next_vert_x);
	printf("diff_x %d\n",dist_to_next_vert_intersect_x);
	if (cos(p->angle) < 0.01 &&  cos(p->angle) > -0.01 )
		next_vert_y = 111111111;
	else
	{
		dist_to_next_vert_intersect = fabs(dist_to_next_vert_x / cos(p->angle));
	printf("					dist_to_next_vert_intersect %f\n", dist_to_next_vert_intersect);	
		next_vert_y = (int)(dist_to_next_vert_intersect * sin(p->angle) +(p->y));
	}
	printf("						next_vert_y: %d\n", next_vert_y);
	draww_point(scene, next_vert_y, next_vert_x);
}