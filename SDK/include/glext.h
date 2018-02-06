#ifndef __glext_h_
#define __glext_h_

#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright 1998, 1999, NVIDIA Corporation.
** All rights Reserved.
**
** THE INFORMATION CONTAINED HEREIN IS PROPRIETARY AND CONFIDENTIAL TO
** NVIDIA, CORPORATION.  USE, REPRODUCTION OR DISCLOSURE TO ANY THIRD PARTY
** IS SUBJECT TO WRITTEN PRE-APPROVAL BY NVIDIA, CORPORATION.
*/

/* Include <GL/glext.h> after <GL/gl.h> in your source files! */

/*************************************************************/

/* Extensions */
#define GL_ARB_multitexture                 1
#define GL_EXT_abgr                         1
#ifndef GL_EXT_bgra
#define GL_EXT_bgra                         1
#endif
#define GL_EXT_blend_color                  1
#define GL_EXT_blend_minmax                 1
#define GL_EXT_blend_subtract               1
#define GL_EXT_clip_volume_hint             1
#define GL_EXT_compiled_vertex_array        1
#define GL_EXT_fog_coord                    1
#define GL_EXT_light_max_exponent           1
#define GL_EXT_packed_pixels                1
#ifndef GL_EXT_paletted_texture
#define GL_EXT_paletted_texture             1
#endif
#define GL_EXT_point_parameters             1
#define GL_EXT_rescale_normal               1
#define GL_EXT_secondary_color              1
#define GL_EXT_separate_specular_color      1
#define GL_EXT_shared_texture_palette       1
#define GL_EXT_stencil_wrap                 1
#define GL_EXT_texture_cube_map             1
#define GL_EXT_texture_env_add              1
#define GL_EXT_texture_env_combine          1
#define GL_EXT_texture_filter_anisotropic   1
#define GL_EXT_texture_lod_bias             1
#ifndef GL_EXT_vertex_array
#define GL_EXT_vertex_array                 1
#endif
#define GL_EXT_vertex_weighting             1
#define GL_NV_blend_square                  1
#define GL_NV_fog_distance                  1
#define GL_NV_register_combiners            1
#define GL_NV_texgen_emboss                 1
#define GL_NV_texgen_reflection             1
#define GL_NV_texture_env_combine4          1
#define GL_NV_vertex_array_range            1
#define GL_SGIS_multitexture                1
#define GL_SGIS_texture_lod                 1
#define WGL_EXT_swap_control                1

/* EXT_abgr */
#define GL_ABGR_EXT                         0x8000

/* EXT_blend_color */
#define GL_CONSTANT_COLOR_EXT               0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT     0x8002
#define GL_CONSTANT_ALPHA_EXT               0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT     0x8004
#define GL_BLEND_COLOR_EXT                  0x8005

/* EXT_blend_minmax */
#define GL_FUNC_ADD_EXT                     0x8006
#define GL_MIN_EXT                          0x8007
#define GL_MAX_EXT                          0x8008
#define GL_BLEND_EQUATION_EXT               0x8009

/* EXT_blend_subtract */
#define GL_FUNC_SUBTRACT_EXT                0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT        0x800B

/* EXT_packed_pixels */
#define GL_UNSIGNED_BYTE_3_3_2_EXT          0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT       0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT       0x8034
#define GL_UNSIGNED_INT_8_8_8_8_EXT         0x8035
#define GL_UNSIGNED_INT_10_10_10_2_EXT      0x8036

/* OpenGL12 */
#ifndef GL_VERSION_1_2
#define GL_RESCALE_NORMAL                   0x803A
#define GL_MAX_ELEMENTS_VERTICES            0x80E8
#define GL_MAX_ELEMENTS_INDICES             0x80E9
#define GL_CLAMP_TO_EDGE                    0x812F
#define GL_TEXTURE_MIN_LOD                  0x813A
#define GL_TEXTURE_MAX_LOD                  0x813B
#define GL_TEXTURE_BASE_LEVEL               0x813C
#define GL_TEXTURE_MAX_LEVEL                0x813D
#define GL_SINGLE_COLOR                     0x81F9
#define GL_SEPARATE_SPECULAR_COLOR          0x81FA
#define GL_LIGHT_MODEL_COLOR_CONTROL        0x81F8
#endif

/* ARB_imaging */
#ifndef ARB_imaging
#define GL_CONSTANT_COLOR                   0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR         0x8002
#define GL_CONSTANT_ALPHA                   0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA         0x8004
#define GL_BLEND_COLOR                      0x8005
#define GL_FUNC_ADD                         0x8006
#define GL_MIN                              0x8007
#define GL_MAX                              0x8008
#define GL_BLEND_EQUATION                   0x8009
#define GL_FUNC_SUBTRACT                    0x800A
#define GL_FUNC_REVERSE_SUBTRACT            0x800B
#endif

/* EXT_vertex_array */
#ifndef GL_VERTEX_ARRAY_EXT
#define GL_VERTEX_ARRAY_EXT                 0x8074
#define GL_NORMAL_ARRAY_EXT                 0x8075
#define GL_COLOR_ARRAY_EXT                  0x8076
#define GL_INDEX_ARRAY_EXT                  0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT          0x8078
#define GL_EDGE_FLAG_ARRAY_EXT              0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT            0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT            0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT          0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT           0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT            0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT          0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT           0x8080
#define GL_COLOR_ARRAY_SIZE_EXT             0x8081
#define GL_COLOR_ARRAY_TYPE_EXT             0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT           0x8083
#define GL_COLOR_ARRAY_COUNT_EXT            0x8084
#define GL_INDEX_ARRAY_TYPE_EXT             0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT           0x8086
#define GL_INDEX_ARRAY_COUNT_EXT            0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT     0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT     0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT   0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT    0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT       0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT        0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT         0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT         0x808F
#define GL_COLOR_ARRAY_POINTER_EXT          0x8090
#define GL_INDEX_ARRAY_POINTER_EXT          0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT  0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT      0x8093
#endif

/* EXT_color_table */
#ifndef GL_COLOR_TABLE_FORMAT_EXT
#define GL_TABLE_TOO_LARGE_EXT              0x8031
#define GL_COLOR_TABLE_FORMAT_EXT           0x80D8
#define GL_COLOR_TABLE_WIDTH_EXT            0x80D9
#define GL_COLOR_TABLE_RED_SIZE_EXT         0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_EXT       0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_EXT        0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT       0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT   0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT   0x80DF
#endif

/* EXT_bgra */
#ifndef GL_BGR_EXT
#define GL_BGR_EXT                          0x80E0
#define GL_BGRA_EXT                         0x80E1
#endif

/* SGIS_texture_lod */
#define GL_TEXTURE_MIN_LOD_SGIS             0x813A
#define GL_TEXTURE_MAX_LOD_SGIS             0x813B
#define GL_TEXTURE_BASE_LEVEL_SGIS          0x813C
#define GL_TEXTURE_MAX_LEVEL_SGIS           0x813D

/* EXT_paletted_texture */
#ifndef GL_COLOR_INDEX1_EXT
#define GL_COLOR_INDEX1_EXT                 0x80E2
#define GL_COLOR_INDEX2_EXT                 0x80E3
#define GL_COLOR_INDEX4_EXT                 0x80E4
#define GL_COLOR_INDEX8_EXT                 0x80E5
#define GL_COLOR_INDEX12_EXT                0x80E6
#define GL_COLOR_INDEX16_EXT                0x80E7
#endif

/* EXT_clip_volume_hint */
#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT    0x80F0

/* EXT_point_parameters */
#define GL_POINT_SIZE_MIN_EXT               0x8126
#define GL_POINT_SIZE_MAX_EXT               0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT    0x8128
#define GL_DISTANCE_ATTENUATION_EXT         0x8129

/* EXT_compiled_vertex_array */
#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT     0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT     0x81A9

/* EXT_shared_texture_palette */
#define GL_SHARED_TEXTURE_PALETTE_EXT       0x81FB

/* SGIS_multitexture */
#define GL_SELECTED_TEXTURE_SGIS            0x835C
#define GL_MAX_TEXTURES_SGIS                0x835D
#define GL_TEXTURE0_SGIS                    0x835E
#define GL_TEXTURE1_SGIS                    0x835F
#define GL_TEXTURE2_SGIS                    0x8360
#define GL_TEXTURE3_SGIS                    0x8361

/* ARB_multitexture */
#define GL_ACTIVE_TEXTURE_ARB               0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB        0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB            0x84E2
#define GL_TEXTURE0_ARB                     0x84C0
#define GL_TEXTURE1_ARB                     0x84C1
#define GL_TEXTURE2_ARB                     0x84C2
#define GL_TEXTURE3_ARB                     0x84C3
#define GL_TEXTURE4_ARB                     0x84C4
#define GL_TEXTURE5_ARB                     0x84C5
#define GL_TEXTURE6_ARB                     0x84C6
#define GL_TEXTURE7_ARB                     0x84C7
#define GL_TEXTURE8_ARB                     0x84C8
#define GL_TEXTURE9_ARB                     0x84C9
#define GL_TEXTURE10_ARB                    0x84CA
#define GL_TEXTURE11_ARB                    0x84CB
#define GL_TEXTURE12_ARB                    0x84CC
#define GL_TEXTURE13_ARB                    0x84CD
#define GL_TEXTURE14_ARB                    0x84CE
#define GL_TEXTURE15_ARB                    0x84CF
#define GL_TEXTURE16_ARB                    0x84D0
#define GL_TEXTURE17_ARB                    0x84D1
#define GL_TEXTURE18_ARB                    0x84D2
#define GL_TEXTURE19_ARB                    0x84D3
#define GL_TEXTURE20_ARB                    0x84D4
#define GL_TEXTURE21_ARB                    0x84D5
#define GL_TEXTURE22_ARB                    0x84D6
#define GL_TEXTURE23_ARB                    0x84D7
#define GL_TEXTURE24_ARB                    0x84D8
#define GL_TEXTURE25_ARB                    0x84D9
#define GL_TEXTURE26_ARB                    0x84DA
#define GL_TEXTURE27_ARB                    0x84DB
#define GL_TEXTURE28_ARB                    0x84DC
#define GL_TEXTURE29_ARB                    0x84DD
#define GL_TEXTURE30_ARB                    0x84DE
#define GL_TEXTURE31_ARB                    0x84DF

/* EXT_fog_coord */
#define GL_FOG_COORDINATE_SOURCE_EXT        0x8450
#define GL_FOG_COORDINATE_EXT               0x8451
#define GL_FRAGMENT_DEPTH_EXT               0x8452
#define GL_CURRENT_FOG_COORDINATE_EXT       0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT    0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT  0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT 0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT         0x8457

/* EXT_secondary_color */
#define GL_COLOR_SUM_EXT                    0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT      0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT   0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT   0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT 0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT 0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT        0x845E

/* EXT_separate_specular_color */
#define GL_SINGLE_COLOR_EXT                 0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT      0x81FA
#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT    0x81F8

/* EXT_rescale_normal */
#define GL_RESCALE_NORMAL_EXT               0x803A

/* EXT_stencil_wrap */
#define GL_INCR_WRAP_EXT                    0x8507
#define GL_DECR_WRAP_EXT                    0x8508

/* EXT_vertex_weighting */
#define GL_MODELVIEW0_MATRIX_EXT            GL_MODELVIEW_MATRIX
#define GL_MODELVIEW1_MATRIX_EXT            0x8506
#define GL_MODELVIEW0_STACK_DEPTH_EXT       GL_MODELVIEW_STACK_DEPTH
#define GL_MODELVIEW1_STACK_DEPTH_EXT       0x8502
#define GL_VERTEX_WEIGHTING_EXT             0x8509
#define GL_MODELVIEW0_EXT                   GL_MODELVIEW
#define GL_MODELVIEW1_EXT                   0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT        0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT          0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT     0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT     0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT   0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT  0x8510

/* NV_texgen_reflection */
#define GL_NORMAL_MAP_NV                    0x8511
#define GL_REFLECTION_MAP_NV                0x8512

/* EXT_texture_cube_map */
#define GL_NORMAL_MAP_EXT                   0x8511
#define GL_REFLECTION_MAP_EXT               0x8512
#define GL_TEXTURE_CUBE_MAP_EXT             0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_EXT     0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT  0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT  0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT  0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT  0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT  0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT  0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_EXT       0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT    0x851C

/* NV_vertex_array_range */
#define GL_VERTEX_ARRAY_RANGE_NV            0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_NV     0x851E
#define GL_VERTEX_ARRAY_RANGE_VALID_NV      0x851F
#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV 0x8520
#define GL_VERTEX_ARRAY_RANGE_POINTER_NV    0x8521

/* NV_register_combiners */
#define GL_REGISTER_COMBINERS_NV            0x8522
#define GL_COMBINER0_NV                     0x8550
#define GL_COMBINER1_NV                     0x8551
#define GL_COMBINER2_NV                     0x8552
#define GL_COMBINER3_NV                     0x8553
#define GL_COMBINER4_NV                     0x8554
#define GL_COMBINER5_NV                     0x8555
#define GL_COMBINER6_NV                     0x8556
#define GL_COMBINER7_NV                     0x8557
#define GL_VARIABLE_A_NV                    0x8523
#define GL_VARIABLE_B_NV                    0x8524
#define GL_VARIABLE_C_NV                    0x8525
#define GL_VARIABLE_D_NV                    0x8526
#define GL_VARIABLE_E_NV                    0x8527
#define GL_VARIABLE_F_NV                    0x8528
#define GL_VARIABLE_G_NV                    0x8529
/*      GL_ZERO */
#define GL_CONSTANT_COLOR0_NV               0x852A
#define GL_CONSTANT_COLOR1_NV               0x852B
/*      GL_FOG */
#define GL_PRIMARY_COLOR_NV                 0x852C
#define GL_SECONDARY_COLOR_NV               0x852D
#define GL_SPARE0_NV                        0x852E
#define GL_SPARE1_NV                        0x852F
/*      GL_TEXTURE0_ARB */
/*      GL_TEXTURE1_ARB */
#define GL_UNSIGNED_IDENTITY_NV             0x8536
#define GL_UNSIGNED_INVERT_NV               0x8537
#define GL_EXPAND_NORMAL_NV                 0x8538
#define GL_EXPAND_NEGATE_NV                 0x8539
#define GL_HALF_BIAS_NORMAL_NV              0x853A
#define GL_HALF_BIAS_NEGATE_NV              0x853B
#define GL_SIGNED_IDENTITY_NV               0x853C
#define GL_SIGNED_NEGATE_NV                 0x853D
#define GL_E_TIMES_F_NV                     0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV   0x8532
/*      GL_NONE */
#define GL_SCALE_BY_TWO_NV                  0x853E
#define GL_SCALE_BY_FOUR_NV                 0x853F
#define GL_SCALE_BY_ONE_HALF_NV             0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV     0x8541
#define GL_DISCARD_NV                       0x8530
#define GL_COMBINER_INPUT_NV                0x8542
#define GL_COMBINER_MAPPING_NV              0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV      0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV       0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV       0x8546
#define GL_COMBINER_MUX_SUM_NV              0x8547
#define GL_COMBINER_SCALE_NV                0x8548
#define GL_COMBINER_BIAS_NV                 0x8549
#define GL_COMBINER_AB_OUTPUT_NV            0x854a
#define GL_COMBINER_CD_OUTPUT_NV            0x854b
#define GL_COMBINER_SUM_OUTPUT_NV           0x854c
#define GL_MAX_GENERAL_COMBINERS_NV         0x854d
#define GL_NUM_GENERAL_COMBINERS_NV         0x854e
#define GL_COLOR_SUM_CLAMP_NV               0x854f

/* NV_fog_distance */
#define GL_FOG_DISTANCE_MODE_NV             0x855a
#define GL_EYE_RADIAL_NV                    0x855b
/*      GL_EYE_PLANE */
#define GL_EYE_PLANE_ABSOLUTE_NV            0x855c

/* NV_texgen_emboss */
#define GL_EMBOSS_LIGHT_NV                  0x855d
#define GL_EMBOSS_CONSTANT_NV               0x855e
#define GL_EMBOSS_MAP_NV                    0x855f

/* EXT_light_max_exponent */
#define GL_MAX_SHININESS_EXT                0x8504
#define GL_MAX_SPOT_EXPONENT_EXT            0x8505

/* EXT_texture_env_combine */
#define GL_COMBINE_EXT                      0x8570
#define GL_COMBINE_RGB_EXT                  0x8571
#define GL_COMBINE_ALPHA_EXT                0x8572
#define GL_RGB_SCALE_EXT                    0x8573
#define GL_ADD_SIGNED_EXT                   0x8574
#define GL_INTERPOLATE_EXT                  0x8575
#define GL_CONSTANT_EXT                     0x8576
#define GL_PRIMARY_COLOR_EXT                0x8577
#define GL_PREVIOUS_EXT                     0x8578
#define GL_SOURCE0_RGB_EXT                  0x8580
#define GL_SOURCE1_RGB_EXT                  0x8581
#define GL_SOURCE2_RGB_EXT                  0x8582
#define GL_SOURCE0_ALPHA_EXT                0x8588
#define GL_SOURCE1_ALPHA_EXT                0x8589
#define GL_SOURCE2_ALPHA_EXT                0x858A
#define GL_OPERAND0_RGB_EXT                 0x8590
#define GL_OPERAND1_RGB_EXT                 0x8591
#define GL_OPERAND2_RGB_EXT                 0x8592
#define GL_OPERAND0_ALPHA_EXT               0x8598
#define GL_OPERAND1_ALPHA_EXT               0x8599
#define GL_OPERAND2_ALPHA_EXT               0x859A

/* NV_texture_env_combine4 */
#define GL_COMBINE4_NV                      0x8503
#define GL_SOURCE3_RGB_NV                   0x8583
#define GL_SOURCE3_ALPHA_NV                 0x858B
#define GL_OPERAND3_RGB_NV                  0x8593
#define GL_OPERAND3_ALPHA_NV                0x859B

/* EXT_texture_filter_anisotropic */
#define GL_TEXTURE_MAX_ANISOTROPY_EXT       0x84fe
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT   0x84ff

/* EXT_texture_lod_bias */
#define GL_MAX_TEXTURE_LOD_BIAS_EXT         0x84fd
#define GL_TEXTURE_FILTER_CONTROL_EXT       0x8500
#define GL_TEXTURE_LOD_BIAS_EXT             0x8501

/*************************************************************/

#ifdef _WIN32

/* This is from Win32's <windef.h> */
# ifndef APIENTRY
#  define GLEXT_APIENTRY_DEFINED
#  if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#   define APIENTRY    __stdcall
#  else
#   define APIENTRY
#  endif
# endif

/* EXT_vertex_array */
typedef void (APIENTRY * PFNGLARRAYELEMENTEXTPROC) (GLint i);
typedef void (APIENTRY * PFNGLCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLDRAWARRAYSEXTPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRY * PFNGLEDGEFLAGPOINTEREXTPROC) (GLsizei stride, GLsizei count, const GLboolean *pointer);
typedef void (APIENTRY * PFNGLGETPOINTERVEXTPROC) (GLenum pname, GLvoid* *params);
typedef void (APIENTRY * PFNGLINDEXPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLNORMALPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLTEXCOORDPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLVERTEXPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);

/* EXT_color_subtable */
typedef void (APIENTRY * PFNGLCOLORSUBTABLEEXTPROC) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *table);

/* EXT_color_table */
typedef void (APIENTRY * PFNGLCOLORTABLEEXTPROC) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (APIENTRY * PFNGLCOPYCOLORTABLEEXTPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * PFNGLGETCOLORTABLEEXTPROC) (GLenum target, GLenum format, GLenum type, GLvoid *table);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERFVEXTPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERIVEXTPROC) (GLenum target, GLenum pname, GLint *params);

/* EXT_compiled_vertex_array */
typedef void (APIENTRY * PFNGLLOCKARRAYSEXTPROC) (GLint first, GLsizei count);
typedef void (APIENTRY * PFNGLUNLOCKARRAYSEXTPROC) (void);

/* WIN_swap_hint */
typedef void (APIENTRY * PFNGLADDSWAPHINTRECTWINPROC) (GLint x, GLint y, GLsizei width, GLsizei height);

/* EXT_point_parameter */
typedef void (APIENTRY * PFNGLPOINTPARAMETERFEXTPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * PFNGLPOINTPARAMETERFVEXTPROC) (GLenum pname, const GLfloat *params);

/* ARB_multitexture */
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DARBPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FARBPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IARBPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SARBPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DARBPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IARBPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SARBPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IARBPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IARBPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum target);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum target);

/* SGIS_multitexture */
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DSGISPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVSGISPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FSGISPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVSGISPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1ISGISPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVSGISPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SSGISPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVSGISPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DSGISPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVSGISPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FSGISPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVSGISPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2ISGISPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVSGISPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SSGISPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVSGISPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DSGISPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVSGISPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FSGISPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVSGISPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3ISGISPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVSGISPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SSGISPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVSGISPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DSGISPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVSGISPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FSGISPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVSGISPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4ISGISPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVSGISPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SSGISPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVSGISPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORDPOINTERSGISPROC) (GLenum target, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLSELECTTEXTURESGISPROC) (GLenum target);
typedef void (APIENTRY * PFNGLSELECTTEXTURECOORDSETSGISPROC) (GLenum target);

/* EXT_vertex_weighting */
typedef void (APIENTRY * PFNGLVERTEXWEIGHTFEXTPROC) (GLfloat weight);
typedef void (APIENTRY * PFNGLVERTEXWEIGHTFVEXTPROC) (const GLfloat *weight);
typedef void (APIENTRY * PFNGLVERTEXWEIGHTPOINTEREXTPROC) (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);

/* EXT_blend_color */
typedef void (APIENTRY * PFNGLBLENDCOLOREXTPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

/* EXT_blend_minmax */
typedef void (APIENTRY * PFNGLBLENDEQUATIONEXTPROC) (GLenum mode);

/* EXT_fog_coord */
typedef void (APIENTRY * PFNGLFOGCOORDDEXTPROC) (GLdouble fog);
typedef void (APIENTRY * PFNGLFOGCOORDDVEXTPROC) (const GLdouble *fog);
typedef void (APIENTRY * PFNGLFOGCOORDFEXTPROC) (GLfloat fog);
typedef void (APIENTRY * PFNGLFOGCOORDFVEXTPROC) (const GLfloat *fog);
typedef void (APIENTRY * PFNGLFOGCOORDPOINTEREXTPROC) (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);

/* EXT_secondary_color */
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3BEXTPROC) (GLbyte red, GLbyte green, GLbyte blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3BVEXTPROC) (const GLbyte *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3DEXTPROC) (GLdouble red, GLdouble green, GLdouble blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3DVEXTPROC) (const GLdouble *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3FEXTPROC) (GLfloat red, GLfloat green, GLfloat blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3FVEXTPROC) (const GLfloat *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3IEXTPROC) (GLint red, GLint green, GLint blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3IVEXTPROC) (const GLint *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3SEXTPROC) (GLshort red, GLshort green, GLshort blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3SVEXTPROC) (const GLshort *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UBEXTPROC) (GLubyte red, GLubyte green, GLubyte blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UBVEXTPROC) (const GLubyte *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UIEXTPROC) (GLuint red, GLuint green, GLuint blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UIVEXTPROC) (const GLuint *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3USEXTPROC) (GLushort red, GLushort green, GLushort blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3USVEXTPROC) (const GLushort *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

/* NV_vertex_array_range */
typedef void (APIENTRY * PFNGLFLUSHVERTEXARRAYRANGENVPROC) (void);
typedef void (APIENTRY * PFNGLVERTEXARRAYRANGENVPROC) (GLsizei size, const GLvoid *pointer);
typedef GLvoid* (APIENTRY * PFNWGLALLOCATEMEMORYNVPROC) (GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
typedef void (APIENTRY * PFNWGLFREEMEMORYNVPROC) (GLvoid *pointer);

/* NV_register_combiners */
typedef void (APIENTRY * PFNGLCOMBINERPARAMETERFVNVPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PFNGLCOMBINERPARAMETERFNVPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * PFNGLCOMBINERPARAMETERIVNVPROC) (GLenum pname, const GLint *params);
typedef void (APIENTRY * PFNGLCOMBINERPARAMETERINVPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * PFNGLCOMBINERINPUTNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (APIENTRY * PFNGLCOMBINEROUTPUTNVPROC) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
typedef void (APIENTRY * PFNGLFINALCOMBINERINPUTNVPROC) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (APIENTRY * PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC) (GLenum variable, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC) (GLenum variable, GLenum pname, GLint *params);

/* WGL_EXT_swap_control */
typedef int (APIENTRY * PFNWGLSWAPINTERVALEXTPROC) (int);
typedef int (APIENTRY * PFNWGLGETSWAPINTERVALEXTPROC) (void);

# ifdef GLEXT_APIENTRY_DEFINED
#  undef GLEXT_APIENTRY_DEFINED
#  undef APIENTRY
# endif

#endif

#ifdef __cplusplus
}
#endif

#endif /* __gl_h_ */
