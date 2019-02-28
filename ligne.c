void ligne(t_fdf *env, int pt, int color) {
	int *pixels = (int *)env->info;
	int x0;  
	int y0;
	int y1;
	int x1;
	int i;
	int xinc, yinc;
	int cumul;

		x0 = env->zoom * env->coord[pt][0];
		y0 = env->zoom * env->coord[pt][1];
		x1 = env->zoom * env->coord[pt + 1][0];
		y1 = env->zoom * env->coord[pt + 1][1];
		iso (&x0, &y0, env->coord[pt][2]);
		iso (&x1, &y1, env->coord[pt +1][2]);
		
		printf (" FROM PT %d : %d, %d -> TO PT %d, %d, %d\n", pt, x0, y0, (pt+1), x1, y1);
		int dx = x1 - x0;
		int dy = y1 - y0;
		xinc = ( dx > 0 ) ? 1 : -1 ;
 		yinc = ( dy > 0 ) ? 1 : -1 ;

		printf ("PT %d DX %d DY %d yo\n", pt, dx, dy);
      	if (y0 >= 0 && y0 < 2560 && x0 >= 0 && x0 < 2560)
			pixels[(y0 * 2560 + x0)] = color;
		if ( dx > dy ) 
		{
			printf("CON... vent si ontionene\n");
			
    		cumul = dx / 2 ;
   			 for ( i = 1 ; i <= dx ; i++ ) 
			{
      			x0 += xinc ;
      			cumul += dy ;
      			if ( cumul >= dx ) 
				{
        			cumul -= dx ;
        			y0 += yinc ; 
				}
		//		printf ("color %d \n", (y0 * env->x_width + x0));
      			if (y0 >= 0 && y0 < 2560 && x0 >= 0 && x0 < 2560)
      				pixels[(y0 * 2560 + x0)] = color; 
	  		} 
		}
    else 
	{
	printf("coming in else BITCHES\n");
    cumul = dy / 2 ;
    for ( i = 1 ; i <= dy ; i++ ) 
	{
    	  y0 += yinc ;
      	cumul += dx ;
     	 if ( cumul >= dy ) {
     	   cumul -= dy ;
     	   x0 += xinc ; }
     	pixels[(y0 * 2560 + x0)] = color;
		 // printf ("coloring %d\n", (y0 * env->x_width* env->zoom + x0));
	  }
	}
}