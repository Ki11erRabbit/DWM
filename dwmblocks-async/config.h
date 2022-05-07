#define CMDLENGTH 60
#define DELIMITER "  "
#define LEADING_DELIMITER " "
#define CLICKABLE_BLOCKS

const Block blocks[] = {
	/*Command*/             /*Update Interval*/     /*Update Signal*/
	BLOCK("block-mailbox", 900, 17),
	BLOCK("block-music",   0,    18),
	//BLOCK("sb-disk",    1800, 19),
	//BLOCK("sb-memory",  10,   20),
	//BLOCK("sb-loadavg", 5,    21),
	//BLOCK("sb-mic",     0,    26),
	//BLOCK("sb-record",  0,    27),
	BLOCK("block-stocks", 600, 14),
	BLOCK("block-weather", 1800, 11),
	BLOCK("block-internet", 5, 4),
	BLOCK("block-volume",  0,    10),
	//BLOCK("free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g", 5, 0),
	BLOCK("block-micstatus",  0,    13),
	BLOCK("block-recording",  0,    9),
	BLOCK("block-battery",  60,   15),
	BLOCK("block-cpu-temp",  5,    0),
	BLOCK("block-cpu-util",  5,    0),
	BLOCK("block-memory",  5,    0),
	BLOCK("block-clockalt", 5, 12),
	//BLOCK("sb-battery", 5,    23),
	//BLOCK("sb-date",    1,    24)
};
