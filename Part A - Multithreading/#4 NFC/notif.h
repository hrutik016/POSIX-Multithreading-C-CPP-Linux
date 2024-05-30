#ifndef __NOTIF_CHAIN_
#define __NOTIF_CHAIN_

#include <stddef.h>     /* for size_t */ 
#include "utils.h"
#include "gluethread/glthread.h"

#define MAX_NOTIF_KEY_SIZE 64

typedef void (*nfc_app_cb) (void *, size_t);


// struct for the notification chain element 
typedef struct notif_chain_elem_{
    char key[MAX_NOTIF_KEY_SIZE];
    size_t key_size;
    bool_t is_key_set;
    nfc_app_cb app_cb;
    glthread_t glue;
}notif_chain_elem_t; 


// MACRO 
GLTHREAD_TO_STRUCT(glthread_glue_to_notif_chain_elem, notif_chain_elem_t, glue);


// struct defination for the noficatino chain linked list 
typedef struct notif_chain_{
    char nfc_name[64];
    glthread_t notif_chain_head;
}notif_chain_t;

// Subscription Request Invoke Function API
void nfc_register_notif_chain(notif_chain_t *nfc, 
                             notif_chain_elem_t *nfce);

// Publisher NFC Invoke Functin API
void nfc_invoke_notif_chain(notif_chain_t *nfc, 
                            void *arg, size_t arg_size, 
                            char*key, size_t key_size);


#endif  /* NOTIF_CHAIN */