/*
    Copyright 2005-2009 Intel Corporation.  All Rights Reserved.

    This file is part of Threading Building Blocks.

    Threading Building Blocks is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    Threading Building Blocks is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Threading Building Blocks; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    As a special exception, you may use this file as part of a free software
    library without restriction.  Specifically, if other files instantiate
    templates or use macros or inline functions from this file, or you compile
    this file and link it with other files to produce an executable, this
    file does not by itself cause the resulting executable to be covered by
    the GNU General Public License.  This exception does not however
    invalidate any other reasons why the executable file might be covered by
    the GNU General Public License.
*/

/*
    The original source for this example is
    Copyright (c) 1994-2008 John E. Stone
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote products
       derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/

/* 
 * shade.c - This file contains the functions that perform surface shading.
 *
 *  $Id: shade.cpp,v 1.3 2007-02-22 17:54:16 dpoulsen Exp $
 */

#include "machine.h"
#include "types.h"
#include "macros.h"
#include "light.h"
#include "intersect.h"
#include "vector.h"
#include "trace.h"
#include "global.h"
#include "shade.h"

void reset_lights(void) {
  numlights=0;
}

void add_light(point_light * li) {
  lightlist[numlights]=li;
  numlights++;
}

color shader(ray * incident) {
  color col, diffuse, phongcol; 
  vector N, L, hit;
  ray shadowray;
  flt inten, t, Llen;
  object * obj;
  int numints, i;
  point_light * li;


  numints=closest_intersection(&t, &obj, incident->intstruct);  
		/* find the number of intersections */
                /* and return the closest one.      */

  if (numints < 1) {         
    /* if there weren't any object intersections then return the */
    /* background color for the pixel color.                     */
    return incident->scene->background;
  }

  if (obj->tex->islight) {  /* if the current object is a light, then we  */
    return obj->tex->col;   /* will only use the objects ambient color    */
  }

  RAYPNT(hit, (*incident), t)       /* find the point of intersection from t */ 
  obj->methods->normal(obj, &hit, incident, &N);  /* find the surface normal */

  /* execute the object's texture function */
  col = obj->tex->texfunc(&hit, obj->tex, incident); 

  diffuse.r = 0.0; 
  diffuse.g = 0.0; 
  diffuse.b = 0.0; 
  phongcol = diffuse;

  if ((obj->tex->diffuse > 0.0) || (obj->tex->phong > 0.0)) {  
    for (i=0; i<numlights; i++) {   /* loop for light contributions */
      li=lightlist[i];              /* set li=to the current light  */
      VSUB(li->ctr, hit, L)         /* find the light vector        */

      /* calculate the distance to the light from the hit point */
      Llen = sqrt(L.x*L.x + L.y*L.y + L.z*L.z) + EPSILON;

      L.x /= Llen; /* normalize the light direction vector */
      L.y /= Llen;
      L.z /= Llen;

      VDOT(inten, N, L)             /* light intensity              */

      /* add in diffuse lighting for this light if we're facing it */ 
      if (inten > 0.0) {            
        /* test for a shadow */
        shadowray.intstruct = incident->intstruct;
        shadowray.flags = RT_RAY_SHADOW | RT_RAY_BOUNDED; 
        incident->serial++;
        shadowray.serial = incident->serial;
        shadowray.mbox = incident->mbox;
        shadowray.o   = hit;
        shadowray.d   = L;      
        shadowray.maxdist = Llen;
        shadowray.s   = hit;
        shadowray.e = li->ctr;
        shadowray.scene = incident->scene;
        reset_intersection(incident->intstruct);
        intersect_objects(&shadowray);

        if (!shadow_intersection(incident->intstruct, Llen)) {
          /* XXX now that opacity is in the code, have to be more careful */
          ColorAddS(&diffuse, &li->tex->col, inten);

          /* phong type specular highlights */
          if (obj->tex->phong > 0.0) {
            flt phongval;
            phongval = shade_phong(incident, &hit, &N, &L, obj->tex->phongexp); 
            if (obj->tex->phongtype) 
              ColorAddS(&phongcol, &col, phongval);
            else
              ColorAddS(&phongcol, &(li->tex->col), phongval);
          }
        }
      }  
    } 
  }

  ColorScale(&diffuse, obj->tex->diffuse);

  col.r *= (diffuse.r + obj->tex->ambient); /* do a product of the */
  col.g *= (diffuse.g + obj->tex->ambient); /* diffuse intensity with  */
  col.b *= (diffuse.b + obj->tex->ambient); /* object color + ambient  */

  if (obj->tex->phong > 0.0) {
    ColorAccum(&col, &phongcol);
  }

  /* spawn reflection rays if necessary */
  /* note: this will overwrite the old intersection list */
  if (obj->tex->specular > 0.0) {    
    color specol;
    specol = shade_reflection(incident, &hit, &N, obj->tex->specular);
    ColorAccum(&col, &specol);
  }

  /* spawn transmission rays / refraction */
  /* note: this will overwrite the old intersection list */
  if (obj->tex->opacity < 1.0) {      
    color transcol;
    transcol = shade_transmission(incident, &hit, 1.0 - obj->tex->opacity);
    ColorAccum(&col, &transcol);
  }

  return col;    /* return the color of the shaded pixel... */
}


color shade_reflection(ray * incident, vector * hit, vector * N, flt specular) {
  ray specray;
  color col;
  vector R;
 
  VAddS(-2.0 * (incident->d.x * N->x + 
                incident->d.y * N->y + 
                incident->d.z * N->z), N, &incident->d, &R);

  specray.intstruct=incident->intstruct; /* what thread are we   */
  specray.depth=incident->depth - 1;   /* go up a level in recursion depth */
  specray.flags = RT_RAY_REGULAR;      /* infinite ray, to start with */
  specray.serial = incident->serial + 1; /* next serial number */
  specray.mbox = incident->mbox; 
  specray.o=*hit; 
  specray.d=R;			       /* reflect incident ray about normal */
  specray.o=Raypnt(&specray, EPSILON); /* avoid numerical precision bugs */
  specray.maxdist = FHUGE;             /* take any intersection */
  specray.scene=incident->scene;       /* global scenedef info */
  col=trace(&specray);                 /* trace specular reflection ray */ 

  incident->serial = specray.serial;    /* update the serial number */

  ColorScale(&col, specular);

  return col;
}


color shade_transmission(ray * incident, vector * hit, flt trans) {
  ray transray;
  color col;

  transray.intstruct=incident->intstruct; /* what thread are we   */
  transray.depth=incident->depth - 1;    /* go up a level in recursion depth */
  transray.flags = RT_RAY_REGULAR;       /* infinite ray, to start with */
  transray.serial = incident->serial + 1; /* update serial number */
  transray.mbox = incident->mbox;
  transray.o=*hit; 
  transray.d=incident->d;                /* ray continues along incident path */
  transray.o=Raypnt(&transray, EPSILON); /* avoid numerical precision bugs */
  transray.maxdist = FHUGE;              /* take any intersection */
  transray.scene=incident->scene;        /* global scenedef info */
  col=trace(&transray);                  /* trace transmission ray */  

  incident->serial = transray.serial;

  ColorScale(&col, trans);

  return col;
}

flt shade_phong(ray * incident, vector * hit, 
  vector * N, vector * L, flt specpower){
  vector H, V;
  flt inten;

  V = incident->d;
  VScale(&V, -1.0);
  VAdd(&V, L, &H);
  VScale(&H, 0.5);   
  VNorm(&H);
  inten = VDot(N, &H);
  if (inten > 0.0) 
    inten = pow(inten, specpower);
  else 
    inten = 0.0;

  return inten;
} 


