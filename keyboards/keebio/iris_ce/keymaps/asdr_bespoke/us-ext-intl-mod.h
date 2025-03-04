// my special software keymap: // https://github.com/matey-jack/us-de-extended-layout

// Most keys are like US ext intl, so I use their keycodes directly.
// The layout is also designed to work with US ext int'l in a sort of fallback mode.

#define KX_DASH  S(ALGR(US_MINS))

// the software layout has <> swapped with ;:
// we don't need to map ;: because the shift layer is done by the software layout,
// but we need to map <> (less than, greater than).
#define KX_LT KC_SCLN
#define KX_GT KC_COLN

// the software layout moved dead accents to AltGr layer.
// corresponding live characters are in same position as US ANSI keyboard,
// so I use those constants, not defining new ones.
#define KX_DGRV ALGR(KC_GRV)
#define KX_ACUT ALGR(KC_QUOT)

// ^() moved to AltGr layer to make space for +=?
#define KX_CIRC ALGR(KC_6)
#define KX_LPRN ALGR(KC_9)
#define KX_RPRN ALGR(KC_0)

// for use with SEND_STRING we need a different kind of key code
#define S_UDIA  SS_ALGR("y")    // Ü
#define S_ODIA  SS_ALGR("p")    // Ö
#define S_ADIA  SS_ALGR("q")    // Ä
#define S_SS    SS_ALGR("s")    // ß
