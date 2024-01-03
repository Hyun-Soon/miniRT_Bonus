/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:47:20 by dongseo           #+#    #+#             */
/*   Updated: 2024/01/03 09:38:17 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "mlx.h"
# include "trace.h"

void	snapshot(t_param *par, t_img *tar_img);
int		convert_color3_int(t_color3 pixel_color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	anti_aliasing(t_param *par);
void	init_image(t_param *par, t_bool flag);
void	do_anti_aliasing(t_param *par, t_img *tar_img);
int		get_aa_color(t_img aa_img, int i, int j);
#endif
