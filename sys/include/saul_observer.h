/*
 * Copyright (C) 2020 Juergen Fitschen <me@jue.yt>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    sys_saul_observer SAUL observer
 * @ingroup     sys
 * @brief       Observer for SAUL device changes
 *
 * @see @ref drivers_saul
 *
 * @{
 *
 * @file
 * @brief       SAUL observer interface definition
 *
 * @author      Juergen Fitschen <me@jue.yt>
 */

#ifndef SAUL_OBSERVER_H
#define SAUL_OBSERVER_H

#include <stdint.h>

#include "clist.h"
#include "saul.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

// FIXME
#define SAUL_OBSERVER_STACK_SIZE            (1024)
#define SAUL_OBSERVER_PRIO                  (8)

/**
 * @brief   SAUL observer handle
 */
typedef struct {
    clist_node_t list_node;                          /**< event queue list entry             */
    void (*callback)(saul_reg_t *dev, void *arg);    /**< callback function pointer */
    void *arg;                                       /**< callback argument */
} saul_observer_t;

/**
 * @brief   Initilize the observer thread
 */
void saul_observer_init(void);

/**
 * @brief   Trigger change check of a SAUL device
 *
 * @param[in] dev       pointer to the device's SAUL registry entry
 */
void saul_observer_queue_event(saul_reg_t *dev);

/**
 * @brief   Start observing a SAUL device
 *
 * @param[in] dev       SAUL device to observe
 * @param[in] entry     pointer to the observer handle
 */
void saul_observer_add(saul_reg_t *dev, saul_observer_t *entry);

/**
 * @brief   Stop observing a SAUL device
 *
 * @param[in] dev       SAUL device to observe
 * @param[in] entry     pointer to the observer handle
 */
void saul_observer_rm(saul_reg_t *dev, saul_observer_t *entry);

#ifdef __cplusplus
}
#endif

#endif /* SAUL_OBSERVER_H */
/** @} */
