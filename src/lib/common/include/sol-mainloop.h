/*
 * This file is part of the Soletta Project
 *
 * Copyright (C) 2015 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "sol-common-buildopts.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @mainpage Soletta Project Documentation
 *
 * @version 1
 * @date 2015
 *
 * Soletta project is a framework for making IoT devices. With Soletta
 * project's libraries developers can easily write software for
 * devices that control actuators/sensors and communicate using
 * standard technologies. It enables adding smartness even on the
 * smallest edge devices.
 *
 * Portable and scalable, it abstracts details of hardware and OS,
 * enabling developers to reuse their code and knowledge on different
 * targets.
 *
 * For a better reference, check the following groups:
 * @li @ref Certificate
 * @li @ref Comms
 * @li @ref Datatypes
 * @li @ref Flow
 * @li @ref IO
 * @li @ref Log
 * @li @ref Macros
 * @li @ref Mainloop
 * @li @ref Meta
 * @li @ref Parsers
 * @li @ref PinMux
 * @li @ref Platform
 * @li @ref PowerSupply
 * @li @ref Types
 * @li @ref Update
 * @li @ref Utils
 * @li @ref WorkerThread
 *
 * Please see the @ref authors page for contact details.
 */

/**
 * @page authors Authors
 *
 * @author Anselmo L. S. Melo <anselmo.melo@intel.com>
 * @author Bruno Bottazzini <bruno.bottazzini@intel.com>
 * @author Bruno Dilly <bruno.dilly@intel.com>
 * @author Caio Marcelo de Oliveira Filho <caio.oliveira@intel.com>
 * @author Ederson de Souza <ederson.desouza@intel.com>
 * @author Flavio Ceolin <flavio.ceolin@intel.com>
 * @author Gustavo Lima Chaves <gustavo.lima.chaves@intel.com>
 * @author Gustavo Sverzut Barbieri <gustavo.barbieri@intel.com>
 * @author Iván Briano <ivan.briano@intel.com>
 * @author José Roberto de Souza <jose.souza@intel.com>
 * @author Leandro Dorileo <leandro.maciel.dorileo@intel.com>
 * @author Leandro Pereira <leandro.pereira@intel.com>
 * @author Lucas De Marchi <lucas.demarchi@intel.com>
 * @author Luis Felipe Strano Moraes <luis.strano@intel.com>
 * @author Luiz Ywata <luizg.ywata@intel.com>
 * @author Murilo Belluzzo <murilo.belluzzo@intel.com>
 * @author Ricardo de Almeida Gonzaga <ricardo.gonzaga@intel.com>
 * @author Rodrigo Chiossi <rodrigo.chiossi@intel.com>
 * @author Tomaz Canabrava <tomaz.canabrava@intel.com>
 * @author Ulisses Furquim <ulisses.furquim@intel.com>
 * @author Vinicius Costa Gomes <vinicius.gomes@intel.com>
 *
 * Please contact <soletta-dev@solettaproject.org> to get in contact with the
 * developers and maintainers.
 */

/**
 * @file
 * @brief These routines are used for Soletta's mainloop manipulation.
 */

/**
 * @defgroup Mainloop Mainloop
 *
 * @{
 */

/**
 * @brief Initializes the Soletta library.
 *
 * This function setup all needed infrastructure. It should be called prior
 * the use of any Soletta API.
 *
 * @return @c 0 on success, error code (always negative) otherwise
 *
 * @see sol_shutdown()
 */
int sol_init(void);

/**
 * @brief Runs the main loop.
 *
 * This function executes the main loop and it will return only after
 * sol_quit() or sol_quit_with_code() is called.
 *
 * @return The value passed to sol_quit_with_code(), or EXIT_SUCCESS if
 * terminated by sol_quit()
 */
int sol_run(void);

/**
 * @brief Terminates the main loop.
 *
 * Stops the main loop and sets the return value of sol_run() to EXIT_SUCCESS.
 *
 * @note MT-safe if compiled with threads support.
 */
void sol_quit(void);

/**
 * @brief Terminates the main loop, setting a specific return code.
 *
 * Stops the main loop and sets the return value of sol_run() to @a return_code.
 * Usually used to indicate that the application should end with an error.
 *
 * @param return_code The exit code that @ref sol_run() will return
 *
 * @note MT-safe if compiled with threads support.
 */
void sol_quit_with_code(int return_code);

/**
 * @brief Shutdown Soletta library.
 *
 * This function shuts down Soletta and once it's called, no other Soletta
 * API should be used.
 *
 * @see sol_init()
 */
void sol_shutdown(void);

/**
 * @struct sol_timeout
 *
 * @brief Handle for timers tracking the timeouts.
 */
struct sol_timeout;

/**
 * @brief Adds a function to be called periodically by the main loop.
 *
 * Timeouts are called by the main loop every @a timeout_ms milliseconds for
 * as long as the given function @a cb returns true.
 *
 * @param timeout_ms The period in milliseconds in which the function will be called
 * @param cb The function to call, it will be called every @p timeout_ms until it returns false
 * @param data The user data pointer to pass to the function
 *
 * @return A handle that can be used to delete the timeout
 *
 * @note MT-safe if compiled with threads support.
 */
struct sol_timeout *sol_timeout_add(uint32_t timeout_ms, bool (*cb)(void *data), const void *data);

/**
 * @brief Deletes the given timeout.
 *
 * If it's necessary to keep a created timeout from being called, this function
 * can delete it.
 *
 * @param handle The timeout to delete
 *
 * @return True if the timeout was deleted, false if the handle is invalid or
 * if it had been marked as removed already
 *
 * @note MT-safe if compiled with threads support.
 */
bool sol_timeout_del(struct sol_timeout *handle);

/**
 * @struct sol_idle
 *
 * @brief Handle for idlers.
 *
 * This structure is used to help setup and control Idlers.
 */
struct sol_idle;

/**
 * @brief Adds a function to be called when the application goes idle.
 *
 * Idlers are called when the main loop reaches the idle state. That is, after
 * all pending events have been processed and no timeout has expired. This means
 * that if there's always something to do, an idler function may never be called.
 * Like timeouts, if an idler function returns false, it will be automatically
 * removed, otherwise they will kept to be called until some other event becomes
 * available.
 *
 * @param cb The function to call when the idle state is reached
 * @param data The user data pointer to pass to the function
 *
 * @return A handle that can be used to delete the idler
 *
 * @note MT-safe if compiled with threads support.
 */
struct sol_idle *sol_idle_add(bool (*cb)(void *data), const void *data);

/**
 * @brief Deletes the given idler.
 *
 * @param handle The idler to delete
 *
 * @return True if the idler was deleted, false if the handle is invalid or
 * if it had been marked as removed already
 *
 * @note MT-safe if compiled with threads support.
 */
bool sol_idle_del(struct sol_idle *handle);

/**
 * @def SOL_MAINLOOP_FD_ENABLED
 *
 * This macro is defined by Soletta at build time and will state if
 * file descriptor (fd) functionality is available, this is common in
 * Linux/UNIX environments.
 */
#ifndef SOL_MAINLOOP_FD_ENABLED
/* keep doxygen happy */
#define SOL_MAINLOOP_FD_ENABLED
#undef SOL_MAINLOOP_FD_ENABLED
#endif

#ifdef SOL_MAINLOOP_FD_ENABLED
/**
 * @brief Flags to be used with file descriptor watchers.
 *
 * When passed to sol_fd_add() or sol_fd_set_flags(), these are the events
 * the user is interested in.
 * When received in the callback set with sol_fd_add(), it's the event that
 * was triggered.
 */
enum sol_fd_flags {
    SOL_FD_FLAGS_NONE = 0,
    /**
     * @brief Non-high priority data available to read from the file descriptor.
     */
    SOL_FD_FLAGS_IN   = (1 << 0),
    /**
     * @brief File descriptor available for writing.
     */
    SOL_FD_FLAGS_OUT  = (1 << 1),
    /**
     * @brief High priority data available to read from the file descriptor.
     */
    SOL_FD_FLAGS_PRI  = (1 << 2),
    /**
     * @brief An error occurred on the file descriptor.
     *
     * @note Only valid in the @c active_flags of the callback function.
     */
    SOL_FD_FLAGS_ERR  = (1 << 3),
    /**
     * @brief All the writing ends of the file descriptor were closed.
     *
     * @note Only valid in the @c active_flags of the callback function.
     */
    SOL_FD_FLAGS_HUP  = (1 << 4),
    /**
     * @brief The file descriptor is invalid.
     *
     * @note Only valid in the @c active_flags of the callback function.
     */
    SOL_FD_FLAGS_NVAL = (1 << 5)
};

struct sol_fd;

/**
 * @brief Adds a function to be called when the requested events are triggered by the
 * given file descriptor.
 *
 * @param fd The file descriptor to watch events for
 * @param flags Bitwise ORed set of flags from #sol_fd_flags that are of interest
 * @param cb The function to call on events
 * @param data The user data pointer to pass to the function
 *
 * @return A handle that can be used to delete the file descriptor watcher
 *
 * @note MT-safe if compiled with threads support.
 */
struct sol_fd *sol_fd_add(int fd, uint32_t flags, bool (*cb)(void *data, int fd, uint32_t active_flags), const void *data);

/**
 * @brief Deletes the given file descriptor watcher.
 *
 * @param handle The handle to delete
 *
 * @return True if the handle was deleted, false it is invalid or already marked as removed
 *
 * @note MT-safe if compiled with threads support.
 */
bool sol_fd_del(struct sol_fd *handle);

/**
 * @brief Sets the flags to watch for on the given file descriptor.
 *
 * @param handle The handle to update
 * @param flags The new set of flags to watch for
 *
 * @return True on success, false if the handle is invalid
 *
 * @note MT-safe if compiled with threads support.
 */
bool sol_fd_set_flags(struct sol_fd *handle, uint32_t flags);

/**
 * @brief Removes the given flags from those being watched.
 *
 * @param handle The handle to update
 * @param flags The flags to remove from the set the handle is watching
 *
 * @return True on success, false if the handle is invalid
 *
 * @note MT-safe if compiled with threads support.
 */
bool sol_fd_unset_flags(struct sol_fd *handle, uint32_t flags);

/**
 * @brief Gets the flags being watched for the given handle.
 *
 * @param handle The handle to get the flags for
 *
 * @return The flags that are currently being watched for by the handle
 *
 * @note MT-safe if compiled with threads support.
 */
uint32_t sol_fd_get_flags(const struct sol_fd *handle);
#endif


/**
 * @def SOL_MAINLOOP_FORK_WATCH_ENABLED
 *
 * This macro is defined by Soletta at build time and will state if
 * monitoring (watch) of child process functionality is available,
 * this is common in Linux/UNIX environments.
 */
#ifndef SOL_MAINLOOP_FORK_WATCH_ENABLED
/* keep doxygen happy */
#define SOL_MAINLOOP_FORK_WATCH_ENABLED
#undef SOL_MAINLOOP_FORK_WATCH_ENABLED
#endif

#ifdef SOL_MAINLOOP_FORK_WATCH_ENABLED

/**
 * @brief Handle for child process.
 *
 * This structure is used to setup and control children process.
 */
struct sol_child_watch;

/**
 * @brief Watch for a child process' termination.
 *
 * When launching children processes, applications can watch for their
 * termination and retrieve their exit status by adding watcher with this function.
 * The @a status parameter received by the callback function is the exit code
 * given by the child.
 *
 * @param pid The pid of the process to watch for
 * @param cb The function that will be called
 * @param data The user data pointer to pass to the function
 *
 * @return A handler that can be used to delete the watcher
 *
 * @note MT-safe if compiled with threads support.
 */
struct sol_child_watch *sol_child_watch_add(uint64_t pid, void (*cb)(void *data, uint64_t pid, int status), const void *data);

/**
 * @brief Delete the given child process watcher.
 *
 * This function removes the watcher only, the child process will continue to
 * run normally, and no notification will be received by the parent when it
 * terminates unless a new watcher is put in place.
 *
 * @param handle The handle to remove
 *
 * @return True on success, false if the handle is invalid or it was already marked as removed
 *
 * @note MT-safe if compiled with threads support.
 */
bool sol_child_watch_del(struct sol_child_watch *handle);
#endif

/**
 * @def SOL_NO_API_VERSION
 *
 * This macro is defined by Soletta at build time and will state if
 * @c api_version structure members and related defines shouldn't be
 * used.
 *
 * API Version is used when dynamic libraries are available so we can
 * check in runtime if the structures match expectations. However in
 * static builds such as those in Small OSes it's guaranteed at build
 * time and the space and checks can be saved.
 *
 * Users can rely on macros SOL_SET_API_VERSION() to set these members
 * in a conditional way.
 */
#ifndef SOL_NO_API_VERSION
/* keep doxygen happy */
#define SOL_NO_API_VERSION
#undef SOL_NO_API_VERSION
#endif

/**
 * @def SOL_SET_API_VERSION
 *
 * This macro will cope with #SOL_NO_API_VERSION and allows easy
 * declaration of @c api_version fields.
 *
 * @code
 * struct sol_mainloop_source_type mytype = {
 *     SOL_SET_API_VERSION(.api_version = SOL_MAINLOOP_SOURCE_TYPE_API_VERSION,)
 *     .prepare = my_prepare,
 *     // ...
 * };
 * @endcode
 */
#ifndef SOL_SET_API_VERSION
/* keep doxygen happy */
#define SOL_SET_API_VERSION(x)
#undef SOL_SET_API_VERSION
#endif

/**
 * @brief Structure representing the type of a source of mainloop events.
 */
struct sol_mainloop_source_type {
#ifndef SOL_NO_API_VERSION
#define SOL_MAINLOOP_SOURCE_TYPE_API_VERSION (1)  /**< @brief Compile time API version to be checked during runtime */
    /**
     * @brief must match #SOL_MAINLOOP_SOURCE_TYPE_API_VERSION at runtime.
     */
    uint16_t api_version;
#endif
    /**
     * @brief Function to be called to prepare to check for events.
     *
     * This function will be called before Soletta's main loop query
     * for its own events. In Linux/POSIX, it will be called before
     * poll(). A source may convert its internal monitored resources
     * to Soletta's at this moment, such as issuing sol_timeout_add()
     * or sol_fd_add().
     *
     * If returns @c true, then there are events to be dispatched
     * right away. This will have @c dispatch() to be called, even if
     * @c check() returns false. This will not let the main loop to
     * sleep or block while it wait for events, as the source's events
     * must be dispatched as soon as possible.
     *
     * A source can implement the traditional main loop primitives:
     * @li @c idler: return @c true.
     * @li @c timeout: return @c false and implement @c get_next_timeout().
     * @li @c fd: return @c false.
     *
     * May be NULL, in this case return @c false is assumed.
     */
    bool (*prepare)(void *data);

    /**
     * @brief Function to be called to query the next timeout for the next
     * event in this source.
     *
     * If returns @c true, then @c timeout must be set to the next
     * timeout to expire in this source. Soletta's main loop will
     * gather all timeouts from external sources and internal
     * (registered with sol_timeout_add()) and will schedule a timer
     * interruption to the one that happens sooner, sleeping until
     * then if there are no known events such as in @c prepare(), or
     * idlers registered with sol_idle_add().
     *
     * If returns false, then may sleep forever as no events are
     * expected.
     *
     * A source can implement the traditional main loop primitives:
     * @li @c idler: return @c false.
     * @li @c timeout: return @c true and set @c timeout.
     * @li @c fd: return @c false.
     *
     * May be NULL, in this case return @c false is assumed.
     */
    bool (*get_next_timeout)(void *data, struct timespec *timeout);

    /**
     * @brief Function to be called to check if there are events to be dispatched.
     *
     * If returns @c true, then there are events to be dispatched and
     * @c dispatch() should be called.
     *
     * A source can implement the traditional main loop primitives:
     * @li @c idler: return @c true.
     * @li @c timeout: return @c true if timeouts expired.
     * @li @c fd: return @c true if fds are ready.
     *
     * Must @b not be NULL.
     */
    bool (*check)(void *data);

    /**
     * @brief Function to be called during main loop iterations if @c
     * prepare() or @c check() returns @c true.
     *
     * Must @b not be NULL.
     */
    void (*dispatch)(void *data);

    /**
     * @brief Function to be called when the source is deleted.
     *
     * It is called when the source is explicitly deleted using
     * sol_mainloop_source_del() or when sol_shutdown() is called.
     *
     * May be NULL.
     */
    void (*dispose)(void *data);
};

/**
 * @brief Structure of a Source of mainloop events.
 */
struct sol_mainloop_source;

/**
 * @brief Create a new source of events to the main loop.
 *
 * Some libraries will have their own internal main loop, in the case
 * we should integrate them with Soletta's we do so by adding a new
 * source of events to Soletta's main loop.
 *
 * The source is described by its @a type, a set of functions to be
 * called back at various phases:
 *
 * @li @b prepare called before all other callbacks at each main loop
 *     iteration.
 *
 * @li @b get_next_timeout called before configuring the maximum
 *     timeout to wait for events. The smallest value of all sources
 *     and the first timeout of Soletta's will be used to determine
 *     the value to use (ie: the one to give to poll(2) if using posix
 *     main loop). If returns @c false the main loop can sleep
 *     forever. If not provided, then return @c false is assumed.
 *
 * @li @b check called after all event sources and Soletta's internal
 *     events are polled and are ready to be dispatched. If it returns
 *     @c true, then there are events to be dispatched in this
 *     source.
 *
 * @li @b dispatch called if @c check() returns @c true.
 *
 * @li @c dispose called when the source is deleted. This will
 *     happen at sol_shutdown() if the source is not manually deleted.
 *
 * If a source doesn't know the time for the next event (say an
 * interruption service handler or an internal file descriptor), then
 * further integration work needs to be done. The interruption service
 * handler can use sol_timeout_add() from a thread to schedule a main
 * loop wake, that in turn will run the source's prepare()
 * automatically. Analogously, the internal file descriptors can be
 * added to soletta's at prepare(). If the main loop uses epoll(),
 * that fd can be added to chain the monitoring.
 *
 * @param type the description of the source of main loop events. This
 *        pointer is not modified and is @b not copied, thus it @b
 *        must exist during the lifetime of the source
 * @param data the user data (context) to give to callbacks in @a type
 *
 * @return the new main loop source instance or @c NULL on failure
 *
 * @see sol_mainloop_source_del()
 *
 * @note MT-safe if compiled with threads support.
 */
struct sol_mainloop_source *sol_mainloop_source_add(const struct sol_mainloop_source_type *type, const void *data);

/**
 * @brief Destroy a source of main loop events.
 *
 * @param handle a valid handle previously created with
 *        sol_mainloop_source_add().
 *
 * @see sol_mainloop_source_add()
 *
 * @note MT-safe if compiled with threads support.
 */
void sol_mainloop_source_del(struct sol_mainloop_source *handle);

/**
 * @brief Retrieve the user data (context) given to the source at creation time.
 *
 * @param handle a valid handle previously created with
 *        sol_mainloop_source_add().
 *
 * @return whatever was given to sol_mainloop_source_add() as second
 *         parameter. NULL is a valid return.
 *
 * @see sol_mainloop_source_add()
 *
 * @note MT-safe if compiled with threads support.
 */
void *sol_mainloop_source_get_data(const struct sol_mainloop_source *handle);

/**
 * @brief Structure representing a mainloop implementation (hooks).
 */
struct sol_mainloop_implementation {
#ifndef SOL_NO_API_VERSION
#define SOL_MAINLOOP_IMPLEMENTATION_API_VERSION (1)  /**< compile time API version to be checked during runtime */
    /**
     * must match #SOL_MAINLOOP_IMPLEMENTATION_API_VERSION at runtime.
     */
    uint16_t api_version;
#endif

    /**
     * Function to be called to initialize the mainloop implementation.
     *
     * This function will be called whenever sol_init() is called.
     *
     * Must not be NULL.
     */
    int (*init)(void);

    /**
     * Function to be called to shutdown (cleanup) the mainloop implementation.
     *
     * This function will be called whenever sol_shutdown() is called.
     *
     * Must not be NULL.
     */
    void (*shutdown)(void);

    /**
     * Function to be called to run the mainloop.
     *
     * This function will be called whenever sol_run() is called and
     * it should block until its sibling @c quit is called.
     *
     * Must not be NULL.
     */
    void (*run)(void);

    /**
     * Function to be called to quit the mainloop.
     *
     * This function will be called whenever sol_quit() or
     * sol_quit_with_code() are called and it should stop the blocking
     * event loop executed by its sibling @c run.
     *
     * Do not cleanup resources here, but in the @c shutdown callback.
     *
     * Must not be NULL.
     */
    void (*quit)(void);

    /**
     * Function to be called to register a timeout to be dispatched.
     *
     * This function receives the number of milliseconds since the
     * current time it should wait before calling the given pointer @c
     * cb with the context @c data.
     *
     * After calling @c cb, if it returns @c true, then the timeout is
     * renewed, otherwise it's automatically cancelled and @c
     * timeout_del may not be called. Please note that calling
     * sol_timeout_del() (and thus @c timeout_del) from the callback
     * @c cb and returning @c false @b is a valid case and must be
     * supported (guard against double-free).
     *
     * This function must return an internal handle that will
     * represent the timeout. It will be given to sol_timeout_del() in
     * order to cancel it before it fires.
     *
     * This function will be called whenever sol_timeout_add() is called.
     *
     * Must not be NULL.
     */
    void *(*timeout_add)(uint32_t timeout_ms, bool (*cb)(void *data), const void *data);

    /**
     * Function to be called to remove a timeout to be dispatched.
     *
     * This function receives the handle returned by sol_timeout_add()
     * (and thus @c timeout_add), deleting it so the registered
     * callback is not called anymore.
     *
     * This function returns true if timeout was successfully deleted.
     *
     * This function will be called whenever sol_timeout_del() is called.
     *
     * Must not be NULL.
     */
    bool (*timeout_del)(void *handle);

    /**
     * Function to be called to register an idler to be dispatched.
     *
     * This function will register an entry so the pointer @c cb will
     * be called with the context @c data when there is nothing else
     * to do. This prevents the mainloop from sleeping, as it will
     * keep calling all registered idlers in sequence.
     *
     * After calling @c cb, if it returns @c true, then the idle is
     * renewed, otherwise it's automatically cancelled and @c idle_del
     * may not be called. Please note that calling sol_idle_del() (and
     * thus @c idle_del) from the callback @c cb and returning @c
     * false @b is a valid case and must be supported (guard against
     * double-free).
     *
     * Should exist more than one idle entry, they are executed only
     * once in the order they are registered. At the end it wraps back
     * to the first element and continues.
     *
     * This function must return an internal handle that will
     * represent the idle. It will be given to sol_idle_del() in
     * order to cancel it before it fires.
     *
     * This function will be called whenever sol_idle_add() is called.
     *
     * Must not be NULL.
     */
    void *(*idle_add)(bool (*cb)(void *data), const void *data);

    /**
     * Function to be called to remove an idler to be dispatched.
     *
     * This function receives the handle returned by sol_idle_add()
     * (and thus @c idle_add), deleting it so the registered
     * callback is not called anymore.
     *
     * This function returns true if idle was successfully deleted.
     *
     * This function will be called whenever sol_idle_del() is called.
     *
     * Must not be NULL.
     */
    bool (*idle_del)(void *handle);

#ifdef SOL_MAINLOOP_FD_ENABLED
    /**
     * Function to be called to register an fd watcher.
     *
     * This function will register a file descriptor (@c fd) to be
     * monitored for events defined in @c flags, whenever one of these
     * events happen, @c cb is called providing the context as @c
     * data, the @c fd and the active event flags @c active_flags.
     *
     * After calling @c cb, if it returns @c true, then the fd watcher
     * is renewed, otherwise it's automatically cancelled and @c
     * fd_del may not be called. Please note that calling sol_fd_del()
     * (and thus @c fd_del) from the callback @c cb and returning @c
     * false @b is a valid case and must be supported (guard against
     * double-free).
     *
     * This function must return an internal handle that will
     * represent the fd watcher. It will be given to sol_fd_del() in
     * order to cancel it before it fires.
     *
     * This function will be called whenever sol_fd_add() is called.
     *
     * Must not be NULL.
     *
     * @note the existence of this pointer is conditional to
     * #SOL_MAINLOOP_FD_ENABLED, which is defined when soletta is
     * configured and built.
     */
    void *(*fd_add)(int fd, uint32_t flags, bool (*cb)(void *data, int fd, uint32_t active_flags), const void *data);

    /**
     * Function to be called to remove an fd watcher.
     *
     * This function receives the handle returned by sol_fd_add()
     * (and thus @c fd_add), deleting it so the registered
     * callback is not called anymore.
     *
     * This function returns true if fd watcher was successfully
     * deleted.
     *
     * This function will be called whenever sol_fd_del() is called.
     *
     * Must not be NULL.
     *
     * @note the existence of this pointer is conditional to
     * #SOL_MAINLOOP_FD_ENABLED, which is defined when soletta is
     * configured and built.
     */
    bool (*fd_del)(void *handle);

    /**
     * Function to be called to change the events of fd watcher.
     *
     * This function will change the events @c flags that an existing
     * fd watcher will use.
     *
     * This function will be called whenever sol_fd_set_flags() is
     * called.
     *
     * Must not be NULL.
     *
     * @note the existence of this pointer is conditional to
     * #SOL_MAINLOOP_FD_ENABLED, which is defined when soletta is
     * configured and built.
     */
    bool (*fd_set_flags)(void *handle, uint32_t flags);

    /**
     * Function to be called to retrieve the events of fd watcher.
     *
     * This function will query the events @c flags that an existing
     * fd watcher will use.
     *
     * This function will be called whenever sol_fd_get_flags() is
     * called.
     *
     * Must not be NULL.
     *
     * @note the existence of this pointer is conditional to
     * #SOL_MAINLOOP_FD_ENABLED, which is defined when soletta is
     * configured and built.
     */
    uint32_t (*fd_get_flags)(const void *handle);
#endif

#ifdef SOL_MAINLOOP_FORK_WATCH_ENABLED
    /**
     * Function to be called to register an child process watcher.
     *
     * This function will register a child process identifier (@c pid)
     * to be monitored. Whenever this process exits, then @c cb is
     * called with the given context @c data.
     *
     * This function must return an internal handle that will
     * represent the child monitor. It will be given to
     * sol_child_watch_del() in order to cancel it before it fires.
     *
     * This function will be called whenever sol_child_watch_add() is
     * called.
     *
     * Must not be NULL.
     *
     * @note the existence of this pointer is conditional to
     * #SOL_MAINLOOP_FORK_WATCH_ENABLED, which is defined when soletta is
     * configured and built.
     */
    void *(*child_watch_add)(uint64_t pid, void (*cb)(void *data, uint64_t pid, int status), const void *data);

    /**
     * Function to be called to remove an child process watcher.
     *
     * This function receives the handle returned by
     * sol_child_watch_add() (and thus @c child_watch_add), deleting
     * it so the registered callback is not called anymore.
     *
     * This function returns true if child watch was successfully deleted.
     *
     * This function will be called whenever sol_child_watch_del() is called.
     *
     * Must not be NULL.
     *
     * @note the existence of this pointer is conditional to
     * #SOL_MAINLOOP_FORK_WATCH_ENABLED, which is defined when soletta is
     * configured and built.
     */
    bool (*child_watch_del)(void *handle);
#endif

    /**
     * Function to be called to register a mainloop event source.
     *
     * This function will register an event source that will be called
     * during the mainloop execution, allowing different mainloops to
     * be integrated. The actual functions to be called are defined in
     * @c type.
     *
     * This function must return an internal handle that will
     * represent the source. It will be given to
     * sol_mainloop_source_del() in order to remove it.
     *
     * This function will be called whenever sol_mainloop_source_add()
     * is called.
     *
     * Must not be NULL.
     */
    void *(*source_add)(const struct sol_mainloop_source_type *type, const void *data);

    /**
     * Function to be called to remove mainloop event source.
     *
     * This function receives the handle returned by
     * sol_mainloop_source_add() (and thus @c source_add), deleting
     * it so it is not used anymore.
     *
     * This function will be called whenever sol_mainloop_source_del() is called.
     *
     * Must not be NULL.
     */
    void (*source_del)(void *handle);

    /**
     * Function to be called to retrieve mainloop event source internal data.
     *
     * This function returns the @c data given to @c source_add.
     *
     * This function will be called whenever
     * sol_mainloop_source_get_data() is called.
     *
     * Must not be NULL.
     */
    void *(*source_get_data)(const void *handle);
};

/**
 * Pointer to Soletta's internal mainloop implementation, that is the
 * default to be used if no other is set.
 */
extern const struct sol_mainloop_implementation *SOL_MAINLOOP_IMPLEMENTATION_DEFAULT;

/**
 * @brief Returns the current mainloop implementation in use.
 *
 * By default it is #SOL_MAINLOOP_IMPLEMENTATION_DEFAULT, but can be
 * changed by sol_mainloop_set_implementation().
 *
 * Before accessing the members of the returned pointer check if your
 * known #SOL_MAINLOOP_IMPLEMENTATION_API_VERSION matches its @c
 * api_version field (which is conditional to #SOL_NO_API_VERSION).
 *
 * @return the pointer to the current implementation, always non-null.
 */
const struct sol_mainloop_implementation *sol_mainloop_get_implementation(void);

/**
 * @brief Changes the mainloop implementation.
 *
 * By setting the mainloop implementation one can override the Soletta
 * behavior, this is often useful if libsoletta is being used as a
 * guest library in some system that already hosts one, such as a
 * Node.JS application. In this case we want to forward requests to
 * that mainloop and be as lean as possible.
 *
 * This is an alternative to sol_mainloop_source_add(), in that case
 * Soletta would be the host and other main loops can be the guest,
 * see sol-glib-integration.h for one example.
 *
 * @note Primitives such as sol_idle_add(), sol_idle_del(),
 *       sol_timeout_add(), sol_timeout_del(), sol_fd_add(),
 *       sol_fd_del(), sol_fd_set_flags(), sol_fd_get_flags(),
 *       sol_child_watch_add() and sol_child_watch_del(),
 *       sol_mainloop_source_add(), sol_mainloop_source_del() and
 *       sol_mainloop_source_get_data() may be called from threads,
 *       then handle these as such.
 *
 * @note this function must be called @b before sol_init() is called
 *       the first time, otherwise it will refuse and will return
 *       error.
 *
 * @param impl a valid handle, this means @c api_version field must
 *        match #SOL_MAINLOOP_IMPLEMENTATION_API_VERSION and all
 *        pointers are non-NULL. It is not copied, so the pointer must
 *        be valid until a new one is set to replace it.
 *
 * @return true on success or false on failure.
 */
bool sol_mainloop_set_implementation(const struct sol_mainloop_implementation *impl);

/**
 * @brief Gets the argument count the application was launched with, if any.
 *
 * @return The @c argc value as set by sol_args_set() or #SOL_MAIN()
 */
int sol_argc(void);

/**
 * @brief Gets the list of arguments the application was launched with, if any.
 *
 * @return The @c argv value as set by sol_args_set() or #SOL_MAIN()
 */
char **sol_argv(void);

/**
 * @brief Sets a new list of arguments and its count.
 *
 * A reference to the @a argv pointer will be kept, so it must be valid at least
 * until sol_args_set() is called again to set different arguments.
 * This function is useful in cases where the main application may have
 * arguments to handle and others that need to be passed forward to other
 * sub-systems. For example, the flow systems has node types to retrieve the
 * arguments the application was started with, and these may differ if the
 * application is run as an FBP script, or as a compiled binary, so the FBP
 * interpreter removes its own arguments and uses this function to set the
 * list of arguments that the flow should see.
 *
 * @param argc The count of elements in @a argv
 * @param argv Array of nul terminated strings, each represents one argument
 */
void sol_args_set(int argc, char *argv[]);

/**
 * @brief Structure used to keep the application main callbacks.
 *
 * It's intended to be used through @ref SOL_MAIN_DEFAULT. Keeps
 * the @c startup and @c shutdown callbacks of the application that
 * will be called by @ref SOL_MAIN_DEFAULT when appropriated.
 */
struct sol_main_callbacks {
#ifndef SOL_NO_API_VERSION
#define SOL_MAIN_CALLBACKS_API_VERSION (1)
    uint16_t api_version; /**< @brief API version */
#endif
    uint16_t flags; /**< @brief Application flags */
    void (*startup)(void); /**< @brief Application @c startup function */
    void (*shutdown)(void); /**< @brief Application @c shutdown function */
};

/**
 * @def SOL_MAIN
 *
 * @brief Convenience macro to declare the @c main function and properly
 * initialize and execute a Soletta Application.
 *
 * @warning Prefer to use @ref SOL_MAIN_DEFAULT since it handles different
 * platforms.
 */

/**
 * @def SOL_MAIN_DEFAULT(startup, shutdown)
 * Preferred entry point for Soletta applications.
 *
 * Different platforms may have different ways in which an application is
 * started, so in order to remain portable, Soletta applications should avoid
 * using platform specific main functions.
 *
 * SOL_MAIN_DEFAULT will be defined to something that makes sense for the
 * target platform, ensuring that Soletta is properly initialized before
 * calling the provided @a startup function, where all of the application
 * specific initialization must take place. If they make sense, command line
 * arguments will have been set and can be retrieved with sol_argc() and
 * sol_argv().
 *
 * After @a startup is called, the main loop will start, and once that finishes,
 * the @a shutdown function, if provided, will be called to perform any
 * necessary termination procedures by the application, before Soletta itself
 * is shutdown and the program terminated.
 */

#ifdef SOL_PLATFORM_CONTIKI
#include "sol-mainloop-contiki.h"

#define SOL_MAIN_DEFAULT(STARTUP, SHUTDOWN)               \
    PROCESS(soletta_app_process, "soletta app process");  \
    AUTOSTART_PROCESSES(&soletta_app_process);            \
    PROCESS_THREAD(soletta_app_process, ev, data)         \
    {                                                     \
        sol_mainloop_contiki_event_set(ev, data);         \
        PROCESS_BEGIN();                                  \
        if (sol_init() < 0)                               \
            return EXIT_FAILURE;                          \
        STARTUP();                                        \
        sol_run();                                        \
        while (sol_mainloop_contiki_iter())               \
            PROCESS_WAIT_EVENT();                         \
        SHUTDOWN();                                       \
        sol_shutdown();                                   \
        PROCESS_END();                                    \
    }
#else
#ifdef SOL_PLATFORM_RIOT
#define SOL_MAIN(CALLBACKS) \
    int main(void) { \
        return sol_mainloop_default_main(&(CALLBACKS), 0, NULL); \
    }
#else
#define SOL_MAIN(CALLBACKS)                                          \
    int main(int argc, char *argv[]) {                              \
        return sol_mainloop_default_main(&(CALLBACKS), argc, argv);  \
    }
#endif /* SOL_PLATFORM_RIOT */

#ifdef __cplusplus
#define SOL_MAIN_DEFAULT(STARTUP, SHUTDOWN) \
    static const struct sol_main_callbacks sol_main_callbacks_instance { \
        SOL_SET_API_VERSION(.api_version = SOL_MAIN_CALLBACKS_API_VERSION, ) \
        .flags = 0, \
        .startup = (STARTUP), \
        .shutdown = (SHUTDOWN) \
    }; \
    SOL_MAIN(sol_main_callbacks_instance)
#else
#define SOL_MAIN_DEFAULT(STARTUP, SHUTDOWN) \
    static const struct sol_main_callbacks sol_main_callbacks_instance = { \
        SOL_SET_API_VERSION(.api_version = SOL_MAIN_CALLBACKS_API_VERSION, ) \
        .startup = (STARTUP), \
        .shutdown = (SHUTDOWN) \
    }; \
    SOL_MAIN(sol_main_callbacks_instance)
#endif /* __cplusplus */
#endif /* SOL_PLATFORM_CONTIKI */

/**
 * @brief Helper function called by @ref SOL_MAIN. Shouldn't be called directly.
 *
 * @param callbacks Application callback structure
 * @param argc The count of elements in @a argv
 * @param argv Array of NUL terminated strings, each represents one argument
 *
 * @return @c 0 on success, error code (always negative) otherwise
 */
int sol_mainloop_default_main(const struct sol_main_callbacks *callbacks, int argc, char *argv[]);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
