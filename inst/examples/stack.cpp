#include <deque>

class S : public std::deque<SEXP>
{
    public: ~S()
    {   // destructor: release all SEXPs, so that they can be GC'd
        while (!this->empty()) {
            SEXP obj = this->front();
            this->pop_front();
            R_ReleaseObject(obj);
        }
    }
};

S* get_stack_pointer(SEXP s, bool check_zero=true)  // internal function
{
    if (TYPEOF(s) != EXTPTRSXP)
        Rf_error("not an external pointer");

    SEXP tag = R_ExternalPtrTag(s);  // our convention, this can be anything
    if (TYPEOF(tag) != CHARSXP || strcmp(CHAR(tag), "stack") !=0 )
        Rf_error("not a stack");

    S* sp = (S*)R_ExternalPtrAddr(s);
    if (check_zero && !sp)
        Rf_error("address is 0");

    return sp;
}

void stack_finaliser(SEXP s)  // internal function
{
    // called during garbage collection
    S* sp = get_stack_pointer(s, false);
    if (sp) {
        delete sp;  // destruct S, release SEXPs
        R_ClearExternalPtr(s);
    }
}

extern "C" SEXP C_stack_create()
{
    S* sp = new S();  // stack pointer
    SEXP s = PROTECT(
        R_MakeExternalPtr((void*)sp, /*tag*/mkChar("stack"), R_NilValue)
    );
    R_RegisterCFinalizerEx(s, stack_finaliser, TRUE);  // auto-called on GC
    UNPROTECT(1);
    return s;
}

extern "C" SEXP C_stack_empty(SEXP s)
{
    S* sp = get_stack_pointer(s);
    return Rf_ScalarLogical(sp->empty());
}

extern "C" SEXP C_stack_push(SEXP s, SEXP obj)
{
    S* sp = get_stack_pointer(s);
    R_PreserveObject(obj);
    sp->push_front(obj);
    return R_NilValue;
}

extern "C" SEXP C_stack_pop(SEXP s)
{
    S* sp = get_stack_pointer(s);
    if (sp->empty())
        Rf_error("stack is empty");
    SEXP obj = sp->front();
    sp->pop_front();
    R_ReleaseObject(obj);
    return obj;
}

/* R
stack_create <- function()
    .Call("C_stack_create", PACKAGE="stack")

stack_empty <- function(s)
    .Call("C_stack_empty", s, PACKAGE="stack")

stack_push <- function(s, obj)
    .Call("C_stack_push", s, obj, PACKAGE="stack")

stack_pop <- function(s)
    .Call("C_stack_pop", s, PACKAGE="stack")
R */
