/*
 * Copyright (c) 2015 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Dornierstr. 4
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef _RTEMS_LINKERSET_H
#define _RTEMS_LINKERSET_H

#include <rtems/score/basedefs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define RTEMS_LINKER_SET_BEGIN( set ) \
  _Linker_set_##set##_begin

#define RTEMS_LINKER_SET_END( set ) \
  _Linker_set_##set##_end

#define RTEMS_LINKER_SET_SIZE( set ) \
  ( (size_t) ( _Linker_set_##set##_end - _Linker_set_##set##_begin ) )

#define RTEMS_LINKER_ROSET_DECLARE( set, type ) \
  extern type volatile const RTEMS_LINKER_SET_BEGIN( set )[0]; \
  extern type volatile const RTEMS_LINKER_SET_END( set )[0]

#define RTEMS_LINKER_ROSET( set, type ) \
  type volatile const RTEMS_LINKER_SET_BEGIN( set )[0] \
  RTEMS_SECTION( ".rtemsroset." #set ".begin" ) RTEMS_USED; \
  type volatile const RTEMS_LINKER_SET_END( set )[0] \
  RTEMS_SECTION( ".rtemsroset." #set ".end" ) RTEMS_USED

#define RTEMS_LINKER_ROSET_ITEM_DECLARE( set, type, item ) \
  extern type volatile const _Linker_set_##set##_##item

#define RTEMS_LINKER_ROSET_ITEM_REFERENCE( set, type, item ) \
  static type volatile const * const _Set_reference_##set##_##item \
  RTEMS_SECTION( ".rtemsroset.reference" ) RTEMS_USED = \
  &_Linker_set_##set##_##item

#define RTEMS_LINKER_ROSET_ITEM_ORDERED( set, type, item, order ) \
  type volatile const _Linker_set_##set##_##item \
  RTEMS_SECTION( ".rtemsroset." #set ".content.0." RTEMS_XSTRING( order ) ) \
  RTEMS_USED

#define RTEMS_LINKER_ROSET_ITEM( set, type, item ) \
  type volatile const _Linker_set_##set##_##item \
  RTEMS_SECTION( ".rtemsroset." #set ".content.1" ) RTEMS_USED

#define RTEMS_LINKER_ROSET_CONTENT( set, decl ) \
  decl \
  RTEMS_SECTION( ".rtemsroset." #set ".content" )

#define RTEMS_LINKER_RWSET_DECLARE( set, type ) \
  extern type volatile RTEMS_LINKER_SET_BEGIN( set )[0]; \
  extern type volatile RTEMS_LINKER_SET_END( set )[0]

#define RTEMS_LINKER_RWSET( set, type ) \
  type volatile RTEMS_LINKER_SET_BEGIN( set )[0] \
  RTEMS_SECTION( ".rtemsrwset." #set ".begin" ) RTEMS_USED; \
  type volatile RTEMS_LINKER_SET_END( set )[0] \
  RTEMS_SECTION( ".rtemsrwset." #set ".end" ) RTEMS_USED

#define RTEMS_LINKER_RWSET_ITEM_DECLARE( set, type, item ) \
  extern type volatile _Linker_set_##set##_##item

/*
 * The .rtemsroset is here not a typo.  We must ensure that the references are
 * not a victim of the garbage collection of the linker.  Thus, we place them
 * in a dedicated area of the RTEMS read-only linker set section.
 */
#define RTEMS_LINKER_RWSET_ITEM_REFERENCE( set, type, item ) \
  static type volatile * const _Set_reference_##set##_##item \
  RTEMS_SECTION( ".rtemsroset.reference" ) RTEMS_USED = \
  &_Linker_set_##set##_##item

#define RTEMS_LINKER_RWSET_ITEM_ORDERED( set, type, item, order ) \
  type volatile _Linker_set_##set##_##item \
  RTEMS_SECTION( ".rtemsrwset." #set ".content.0." RTEMS_XSTRING( order ) ) \
  RTEMS_USED

#define RTEMS_LINKER_RWSET_ITEM( set, type, item ) \
  type volatile _Linker_set_##set##_##item \
  RTEMS_SECTION( ".rtemsrwset." #set ".content.1" ) RTEMS_USED

#define RTEMS_LINKER_RWSET_CONTENT( set, decl ) \
  decl \
  RTEMS_SECTION( ".rtemsrwset." #set ".content" )

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RTEMS_LINKERSET_H */
