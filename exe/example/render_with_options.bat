call render_single ..\scenes\r1+r2_01_single_sphere.txt -size 200 200 -depth 9 10
call render_single ..\scenes\r1+r2_02_five_spheres.txt -size 200 200 -depth 8 12
call render ..\scenes\r3_spheres_perspective.txt
call render ..\scenes\r4_colored_lights.txt
call render ..\scenes\r4_diffuse+ambient_ball.txt
call render ..\scenes\r4_diffuse_ball.txt
call render ..\scenes\r4_exponent_variations.txt
call render ..\scenes\r4_exponent_variations_back.txt
call render ..\scenes\r4_point_light_circle.txt
call render ..\scenes\r4_point_light_circle_d2.txt
call render ..\scenes\r5_spheres_plane.txt
call render ..\scenes\r6_bunny_mesh_1000.txt
call render ..\scenes\r6_bunny_mesh_200.txt
call render ..\scenes\r6_cube_orthographic.txt
call render ..\scenes\r6_cube_perspective.txt
call render_single ..\scenes\r7_colored_shadows.txt -size 200 200 -shadows -depth 0 10
call render_single ..\scenes\r7_simple_shadow.txt -size 200 200 -shadows -depth 0 10
call render_single ..\scenes\r8_reflective_sphere.txt -size 200 200 -shadows -bounces 3 -weight 0.01 -depth 0 10
call render ..\scenes\r9_sphere_triangle.txt

call render ..\scenes\extra_xform_axes_cube.txt
call render ..\scenes\extra_xform_rotated_sphere.txt
call render ..\scenes\extra_xform_rotated_squashed_sphere.txt
call render ..\scenes\extra_xform_squashed_sphere.txt
call render ..\scenes\extra_xform_t_scale.txt
call render_single ..\scenes\extra_glass_sphere.txt -size 200 200 -bounces 4 -depth 0 10
