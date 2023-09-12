#include <iostream>
#include <termcap.h>
#include <ncurses.h>

/*
These routines are included as a conversion aid for programs that use the termcap library.  Their parameters are
       the same and the routines are emulated using the terminfo database.  Thus, they can only be used to query the
       capabilities of entries for which a terminfo entry has been compiled.

       The tgetent routine loads the entry for name.  It returns 1 on success, 0 if there is no such entry, and -1 if
       the terminfo database could not be found.  The emulation ignores the buffer pointer bp.

       The tgetflag routine gets the boolean entry for id, or zero if it is not available.

       The tgetnum routine gets the numeric entry for id, or -1 if it is not available.

       The tgetstr routine returns the string entry for id, or zero if it is not available.  Use tputs to output the
       returned string.  The return value will also be copied to the buffer pointed to by area, and the area value will
       be updated to point past the null ending this value.

       Only the first two characters of the id parameter of tgetflag, tgetnum and tgetstr are compared in lookups.

       The tgoto routine instantiates the parameters into the given capability.  The output from this routine is to be
       passed to tputs.

       The tputs routine is described on the curs_terminfo(3X) manual page.  It can retrieve capabilities by either
       termcap or terminfo name.

       The variables PC, UP and BC are set by tgetent to the terminfo entry's data for pad_char, cursor_up and
       backspace_if_not_bs, respectively.  UP is not used by ncurses.  PC is used in the tdelay_output function.  BC is
       used in the tgoto emulation.  The variable ospeed is set by ncurses in a system-specific coding to reflect the
       terminal speed.
    */

int main(int argc, const char * argv[]) {

    char term_buffer[2048]; //buffer for termcap info

    char *termtype = getenv("TERM");

    if (termtype == 0) std::cerr << "Specify a terminal type with `setenv TERM <yourtype>'" << std::endl;

    // Load ther termcap, load the termcap entry for the specified terminal type
    if (tgetent(term_buffer, termtype) < 1) { 
        std::cerr << "Failed to load termcap entry for " << termtype << std::endl;
        return 1;
    }

    // Get a boolean capability33
    if (tgetflag(const_cast<char*>("am"))) {
        std::cout << "Automatic margins are supported" << std::endl;
    } else {
        std::cout << "Automatic margins are not supported" << std::endl;
    }

    // Get a numeric capability
    int columes = tgetnum(const_cast<char*>("co"));
    int rows = tgetnum(const_cast<char*>("li"));
    if (columes != -1 && rows != -1) {
        std::cout << "Terminal size is " << columes << "x" << rows << std::endl;
    } else {
        std::cout << "Failed to get terminal size" << std::endl;
    }


    // Get a string capability
    char* clear_screen = tgetstr(const_cast<char*>("cl"), 0);

    if (clear_screen != nullptr) {
        std::cout << "Clearing the screen..." << std::endl;
        tputs(clear_screen, 1, putchar);
    } else {
        std::cout << "Failed to get clear screen capability" << std::endl;
    }

    return 0;
}