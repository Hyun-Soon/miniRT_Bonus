/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:30:33 by yusekim           #+#    #+#             */
/*   Updated: 2024/01/02 16:44:14 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSE_H
# define MAP_PARSE_H

void		parse_ambient(char **line, t_param *par);
void		parse_camera(char **line, t_param *par);
void		parse_light(char **line, t_param *par);
double		get_uvalue(char *line);
void		parse_sphere(char **line, t_param *par);
// void		parse_sphere(char **line, t_param *par, t_param *par);
void		parse_cylinder(char **line, t_param *par);
void		parse_plane(char **line, t_param *par);
void		parse_cone(char **line, t_param *par);
void		parse_cb(char **line, t_param *par);
void		parse_disk(char **line, t_param *par);
void		parse_light_bulb(char **line, t_param *par);
void		get_maps(t_param *par, t_img *img, char *filepath);

void		split_free(char **split);

int			check_valid_double(const char *str);
double		get_db(const char *str, int idx);
double		atodb(char *str);
int			get_split_cnt(char **split);
t_color3	get_color(char *line);
t_vec3		get_tuple(char *line);
void		split_free(char **split);
double		get_ratio(char *line);
t_vec3		get_normal(char *line);
void		init(t_param *par, char *file_name);
void		init_image(t_param *par, t_bool flag);
void		scene_parse(t_param *par);
#endif
