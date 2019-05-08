#ifdef GLOBAL_MAIN
#define GLOBAL
#define GLOBAL_VAL(X) = X
#else
#define GLOBAL extern
#define GLOBAL_VAL(X)
#endif

#include <stdio.h>
#include <ogg/ogg.h>
#include <stdbool.h>
#include <stddef.h>

GLOBAL struct {
	enum {
		EDIT_NONE,
		EDIT_LIST,
		EDIT_WRITE,
		EDIT_APPEND,
	} edit;
	
	bool gain_fix;
	bool gain_relative;
	bool gain_not_zero;
	bool gain_q78;
	int gain_val;
	bool gain_val_sign;
	bool gain_put;
	
	bool tag_ignore_picture;
	enum  {
		TAG_ESCAPE_TAB,
		TAG_ESCAPE_BACKSLASH,
		TAG_ESCAPE_NUL,
	} tag_escape;
	bool tag_raw;
	bool tag_toupper;
	char *tag_filename;
	bool tag_deferred;
	bool tag_verify;
	bool tag_check_line_term;
	
	int target_idx;
	
	char *in, *out;
} O;

GLOBAL enum {
	PAGE_INFO,
	PAGE_INFO_BORDER,
	PAGE_COMMENT,
	PAGE_OTHER_METADATA,
	PAGE_SOUND,
} opst;

GLOBAL struct codec_parser {
	enum {
		CODEC_OPUS,
		CODEC_COMMON,
		CODEC_FLAC,
		CODEC_VP8,
	} type;
	char const *prog, *name;
	size_t headmagic_len;
	char const *headmagic;
	void (*parse)(ogg_page*);
	size_t commagic_len;
	char const *commagic;
} *codec;

GLOBAL char const *program_name;
GLOBAL char const *program_name_default GLOBAL_VAL("opuscomment");
// "METADATA_BLOCK_PICTURE=" in ASCII
GLOBAL uint8_t const * const MBPeq
	GLOBAL_VAL("\x4d\x45\x54\x41\x44\x41\x54\x41\x5f\x42\x4c\x4f\x43\x4b\x5f\x50\x49\x43\x54\x55\x52\x45\x3d");
GLOBAL uint8_t const * const b64tab_ascii
	GLOBAL_VAL("\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f" // A-O
	"\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a" // P-Z
	"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f" // a-o
	"\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a" // p-z
	"\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39" // 0-9
	"\x2b\x2f\x3d" // + / =
	);


GLOBAL uint32_t opus_idx, opus_sno, opus_idx_diff;
GLOBAL bool leave_header_packets;
// GLOBAL bool have_multi_streams;
GLOBAL bool error_on_thread;

GLOBAL FILE *stream_input, *built_stream, *tag_output;
GLOBAL bool tag_output_to_file;

#ifdef NLS
#include <nl_types.h>
GLOBAL nl_catd catd;
#endif