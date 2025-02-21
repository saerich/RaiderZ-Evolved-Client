/*
 *
 * Copyright (c) 2002-2006, NVIDIA Corporation.
 * 
 *  
 * 
 * NVIDIA Corporation("NVIDIA") supplies this software to you in consideration 
 * of your agreement to the following terms, and your use, installation, 
 * modification or redistribution of this NVIDIA software constitutes 
 * acceptance of these terms.  If you do not agree with these terms, please do 
 * not use, install, modify or redistribute this NVIDIA software.
 * 
 *  
 * 
 * In consideration of your agreement to abide by the following terms, and 
 * subject to these terms, NVIDIA grants you a personal, non-exclusive license,
 * under NVIDIA�s copyrights in this original NVIDIA software (the "NVIDIA 
 * Software"), to use, reproduce, modify and redistribute the NVIDIA 
 * Software, with or without modifications, in source and/or binary forms; 
 * provided that if you redistribute the NVIDIA Software, you must retain the 
 * copyright notice of NVIDIA, this notice and the following text and 
 * disclaimers in all such redistributions of the NVIDIA Software. Neither the 
 * name, trademarks, service marks nor logos of NVIDIA Corporation may be used 
 * to endorse or promote products derived from the NVIDIA Software without 
 * specific prior written permission from NVIDIA.  Except as expressly stated 
 * in this notice, no other rights or licenses express or implied, are granted 
 * by NVIDIA herein, including but not limited to any patent rights that may be 
 * infringed by your derivative works or by other works in which the NVIDIA 
 * Software may be incorporated. No hardware is licensed hereunder. 
 * 
 *  
 * 
 * THE NVIDIA SOFTWARE IS BEING PROVIDED ON AN "AS IS" BASIS, WITHOUT 
 * WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING 
 * WITHOUT LIMITATION, WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR ITS USE AND OPERATION 
 * EITHER ALONE OR IN COMBINATION WITH OTHER PRODUCTS.
 * 
 *  
 * 
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, 
 * EXEMPLARY, CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, LOST 
 * PROFITS; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) OR ARISING IN ANY WAY OUT OF THE USE, 
 * REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE NVIDIA SOFTWARE, 
 * HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING 
 * NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF NVIDIA HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */ 

#ifndef _cggl_h
#define _cggl_h

#include <Cg/cg.h>

#ifdef _WIN32
# ifndef APIENTRY /* From Win32's <windef.h> */
#  define CGGL_APIENTRY_DEFINED
#  if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__) || defined(__LCC__)
#   define APIENTRY    __stdcall
#  else
#   define APIENTRY
#  endif
# endif
# ifndef WINGDIAPI /* From Win32's <wingdi.h> and <winnt.h> */
#  define CGGL_WINGDIAPI_DEFINED
#  define WINGDIAPI __declspec(dllimport)
# endif
#endif /* _WIN32 */

/* Set up for either Win32 import/export/lib. */
#ifndef CGGLDLL_API
# ifdef _WIN32
#  ifdef CGGLDLL_EXPORTS
#   define CGGLDLL_API __declspec(dllexport)
#  elif defined (CG_LIB)
#   define CGGLDLL_API
#  else
#   define CGGLDLL_API __declspec(dllimport)
#  endif
# else
#  define CGGLDLL_API
# endif
#endif

#ifndef CGGLENTRY
# ifdef _WIN32
#  define CGGLENTRY __cdecl
# else
#  define CGGLENTRY
# endif
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*** cgGL Type Definitions                                                 ***/
/*****************************************************************************/

typedef enum
 {
  CG_GL_MATRIX_IDENTITY = 0,
  CG_GL_MATRIX_TRANSPOSE = 1,
  CG_GL_MATRIX_INVERSE = 2,
  CG_GL_MATRIX_INVERSE_TRANSPOSE = 3,

  CG_GL_MODELVIEW_MATRIX,
  CG_GL_PROJECTION_MATRIX,
  CG_GL_TEXTURE_MATRIX,
  CG_GL_MODELVIEW_PROJECTION_MATRIX,

  CG_GL_VERTEX,
  CG_GL_FRAGMENT,

 } CGGLenum;


#ifndef CGGL_EXPLICIT

/******************************************************************************
 *** Profile Functions                                 
 *****************************************************************************/

CGGLDLL_API CGbool CGGLENTRY cgGLIsProfileSupported(CGprofile profile);

CGGLDLL_API void CGGLENTRY cgGLEnableProfile(CGprofile profile);
CGGLDLL_API void CGGLENTRY cgGLDisableProfile(CGprofile profile);

CGGLDLL_API CGprofile CGGLENTRY cgGLGetLatestProfile(CGGLenum profile_type);
CGGLDLL_API void CGGLENTRY cgGLSetOptimalOptions(CGprofile profile);

/******************************************************************************
 *** Program Managment Functions                                 
 *****************************************************************************/

CGGLDLL_API void CGGLENTRY cgGLLoadProgram(CGprogram program);
CGGLDLL_API CGbool CGGLENTRY cgGLIsProgramLoaded(CGprogram program);
CGGLDLL_API void CGGLENTRY cgGLBindProgram(CGprogram program);
CGGLDLL_API void CGGLENTRY cgGLUnbindProgram(CGprofile profile);
CGGLDLL_API GLuint CGGLENTRY cgGLGetProgramID(CGprogram program);

/******************************************************************************
 *** Parameter Managment Functions                                 
 *****************************************************************************/

CGGLDLL_API void CGGLENTRY cgGLSetParameter1f(CGparameter param,
                                    float x);

CGGLDLL_API void CGGLENTRY cgGLSetParameter2f(CGparameter param,
                                    float x,
                                    float y);

CGGLDLL_API void CGGLENTRY cgGLSetParameter3f(CGparameter param,
                                    float x,
                                    float y,
                                    float z);

CGGLDLL_API void CGGLENTRY cgGLSetParameter4f(CGparameter param,
                                    float x,
                                    float y,
                                    float z,
                                    float w);

CGGLDLL_API void CGGLENTRY cgGLSetParameter1fv(CGparameter param, const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameter2fv(CGparameter param, const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameter3fv(CGparameter param, const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameter4fv(CGparameter param, const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameter1d(CGparameter param,
                                    double x);

CGGLDLL_API void CGGLENTRY cgGLSetParameter2d(CGparameter param,
                                    double x,
                                    double y);

CGGLDLL_API void CGGLENTRY cgGLSetParameter3d(CGparameter param,
                                    double x,
                                    double y,
                                    double z);

CGGLDLL_API void CGGLENTRY cgGLSetParameter4d(CGparameter param,
                                    double x,
                                    double y,
                                    double z,
                                    double w);

CGGLDLL_API void CGGLENTRY cgGLSetParameter1dv(CGparameter param, const double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameter2dv(CGparameter param, const double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameter3dv(CGparameter param, const double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameter4dv(CGparameter param, const double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter1f(CGparameter param, float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter2f(CGparameter param, float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter3f(CGparameter param, float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter4f(CGparameter param, float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter1d(CGparameter param, double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter2d(CGparameter param, double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter3d(CGparameter param, double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameter4d(CGparameter param, double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray1f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray2f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray3f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray4f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const float *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray1d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray2d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray3d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterArray4d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         const double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray1f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray2f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray3f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray4f(CGparameter param,
                                         long offset,
                                         long nelements,
                                         float *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray1d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray2d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray3d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         double *v);

CGGLDLL_API void CGGLENTRY cgGLGetParameterArray4d(CGparameter param,
                                         long offset,
                                         long nelements,
                                         double *v);

CGGLDLL_API void CGGLENTRY cgGLSetParameterPointer(CGparameter param,
                                         GLint fsize,
                                         GLenum type,
                                         GLsizei stride,
                                         const GLvoid *pointer);

CGGLDLL_API void CGGLENTRY cgGLEnableClientState(CGparameter param);
CGGLDLL_API void CGGLENTRY cgGLDisableClientState(CGparameter param);

/******************************************************************************
 *** Matrix Parameter Managment Functions                                 
 *****************************************************************************/

CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterdr(CGparameter param, 
                                          const double *matrix);
CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterfr(CGparameter param, 
                                          const float *matrix);
CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterdc(CGparameter param, 
                                          const double *matrix);
CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterfc(CGparameter param, 
                                          const float *matrix);

CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterdr(CGparameter param, double *matrix);
CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterfr(CGparameter param, float *matrix);
CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterdc(CGparameter param, double *matrix);
CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterfc(CGparameter param, float *matrix);

CGGLDLL_API void CGGLENTRY cgGLSetStateMatrixParameter(CGparameter param, 
                                             CGGLenum matrix,
                                             CGGLenum transform);

CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterArrayfc(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               const float *matrices);

CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterArrayfr(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               const float *matrices);

CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterArraydc(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               const double *matrices);

CGGLDLL_API void CGGLENTRY cgGLSetMatrixParameterArraydr(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               const double *matrices);

CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterArrayfc(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               float *matrices);

CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterArrayfr(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               float *matrices);

CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterArraydc(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               double *matrices);

CGGLDLL_API void CGGLENTRY cgGLGetMatrixParameterArraydr(CGparameter param, 
                                               long offset,
                                               long nelements,
                                               double *matrices);

/******************************************************************************
 *** Texture Parameter Managment Functions
 *****************************************************************************/

CGGLDLL_API void CGGLENTRY cgGLSetTextureParameter(CGparameter param, GLuint texobj);
CGGLDLL_API GLuint CGGLENTRY cgGLGetTextureParameter(CGparameter param);
CGGLDLL_API void CGGLENTRY cgGLEnableTextureParameter(CGparameter param);
CGGLDLL_API void CGGLENTRY cgGLDisableTextureParameter(CGparameter param);
CGGLDLL_API GLenum CGGLENTRY cgGLGetTextureEnum(CGparameter param);

CGGLDLL_API void CGGLENTRY cgGLSetManageTextureParameters(CGcontext ctx, CGbool flag);
CGGLDLL_API CGbool CGGLENTRY cgGLGetManageTextureParameters(CGcontext ctx);

CGGLDLL_API void CGGLENTRY cgGLSetupSampler(CGparameter param, GLuint texobj);
CGGLDLL_API void CGGLENTRY cgGLRegisterStates(CGcontext);

CGGLDLL_API void CGGLENTRY cgGLEnableProgramProfiles( CGprogram program );
CGGLDLL_API void CGGLENTRY cgGLDisableProgramProfiles( CGprogram program );

#endif

#ifdef __cplusplus
}
#endif

#ifdef CGGL_APIENTRY_DEFINED
# undef CGGL_APIENTRY_DEFINED
# undef APIENTRY
#endif

#ifdef CGGL_WINGDIAPI_DEFINED
# undef CGGL_WINGDIAPI_DEFINED
# undef WINGDIAPI
#endif

#endif
