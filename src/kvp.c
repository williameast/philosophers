/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:04:08 by William           #+#    #+#             */
/*   Updated: 2025/07/15 18:50:05 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

/* // Initialize t_kvp */
/* t_kvp *kvp_init(long long value) */
/* { */
/*     t_kvp *kvp = malloc(sizeof(t_kvp)); */
/*     if (!kvp) */
/*         return NULL; */
/*     kvp->value = value; */

/*     if (pthread_mutex_init(&kvp->lock, NULL)) */
/*     { */
/*         free(kvp); */
/*         return NULL; */
/*     } */
/*     return kvp; */
/* } */

/* void kvp_access(t_kvp *kvp, void (*operation)(t_kvp *, void *), void *context) */
/* { */
/*     pthread_mutex_lock(&kvp->lock); // Lock the resource */
/*     operation(kvp, context);       // Perform the specific operation */
/*     pthread_mutex_unlock(&kvp->lock); // Unlock the resource */
/* } */

/* void get_operation(t_kvp *kvp, void *context) */
/* { */
/*     *((long long *)context) = kvp->value; // Write the value to the context */
/* } */

/* long long kvp_get(t_kvp *kvp) */
/* { */
/*     long long result = 0; */
/*     kvp_access(kvp, get_operation, &result); */
/*     return result; */
/* } */

/* void set_operation(t_kvp *kvp, void *context) */
/* { */
/*     kvp->value = *(long long *)context; // Read the value from the context */
/* } */

/* void kvp_set(t_kvp *kvp, long long value) */
/* { */
/*     kvp_access(kvp, set_operation, &value); */
/* } */


/* // Destroy t_kvp */
/* void kvp_destroy(t_kvp *kvp) */
/* { */
/*     if (!kvp) */
/*         return; */
/*     pthread_mutex_destroy(&kvp->lock); */
/*     free(kvp); */
/* } */


// Initialize t_kvp
int kvp_init(t_kvp *kvp, long long value)
{
    kvp->value = value;
    if (pthread_mutex_init(&kvp->lock, NULL))
        return -1;
    return 0;
}

void kvp_access(t_kvp *kvp, void (*operation)(t_kvp *, void *), void *context)
{
    pthread_mutex_lock(&kvp->lock); // Lock the resource
    operation(kvp, context);       // Perform the specific operation
    pthread_mutex_unlock(&kvp->lock); // Unlock the resource
}

void get_operation(t_kvp *kvp, void *context)
{
    *((long long *)context) = kvp->value; // Write the value to the context
}

long long kvp_get(t_kvp *kvp)
{
    long long result = 0;
    kvp_access(kvp, get_operation, &result);
    return result;
}

void set_operation(t_kvp *kvp, void *context)
{
    kvp->value = *(long long *)context; // Read the value from the context
}

void kvp_set(t_kvp *kvp, long long value)
{
    kvp_access(kvp, set_operation, &value);
}


// Destroy t_kvp
void kvp_destroy(t_kvp *kvp)
{
    pthread_mutex_destroy(&kvp->lock);
}
