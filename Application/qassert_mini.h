/******************************************************************************
* @file    qassert_mini.h
* @brief   Minimal design-by-contract (assert) interface for embedded projects
* @author  Alexandre Panhaleux
* @license MIT
******************************************************************************/

/* qassert_mini.h - Minimal DbC-style asserts (MIT) */
#ifndef QASSERT_MINI_H_
#define QASSERT_MINI_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef Q_NORETURN
#define Q_NORETURN _Noreturn void
#endif

/* App must provide this (you already do in bsp.c) */
Q_NORETURN Q_onAssert(char const *module, int location);

/* Optional: tag each module for nicer assert messages */
#define Q_DEFINE_THIS_MODULE(name_) \
    static char const Q_this_module_[] = name_;

/* Line-based and ID-based asserts */
#define Q_ASSERT(expr_)          ((expr_) ? (void)0 : Q_onAssert(Q_this_module_, __LINE__))
#define Q_ASSERT_ID(id_, expr_)  ((expr_) ? (void)0 : Q_onAssert(Q_this_module_, (id_)))
#define Q_ERROR()                Q_onAssert(Q_this_module_, __LINE__)
#define Q_ERROR_ID(id_)          Q_onAssert(Q_this_module_, (id_))
#define Q_ALLEGE(expr_)          ((void)(expr_))  /* always evaluates, never calls handler */

#ifdef __cplusplus
}
#endif
#endif /* QASSERT_MINI_H_ */
