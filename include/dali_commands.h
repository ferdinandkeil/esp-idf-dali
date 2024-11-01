#ifndef __DALI_COMMANDS_H__
#define __DALI_COMMANDS_H__

#define DALI_SPECIAL_CMD_GET_ADDRESS(cmd) (cmd >> 8)

#define DALI_COMMAND_OFF                                  0x00 // dec. 0
#define DALI_COMMAND_UP                                   0x01 // dec. 1
#define DALI_COMMAND_DOWN                                 0x02 // dec. 2
#define DALI_COMMAND_STEP_UP                              0x03 // dec. 3
#define DALI_COMMAND_STEP_DOWN                            0x04 // dec. 4
#define DALI_COMMAND_RECALL_MAX_LEVEL                     0x05 // dec. 5
#define DALI_COMMAND_RECALL_MIN_LEVEL                     0x06 // dec. 6
#define DALI_COMMAND_STEP_DOWN_AND_OFF                    0x07 // dec. 7
#define DALI_COMMAND_ON_AND_STEP_UP                       0x08 // dec. 8
#define DALI_COMMAND_ENABLE_DAPC_SEQ                      0x09 // dec. 9
// reserved
#define DALI_COMMAND_GO_TO_SCENE_0                        0x10 // dec. 16
#define DALI_COMMAND_GO_TO_SCENE_1                        0x11 // dec. 17
#define DALI_COMMAND_GO_TO_SCENE_2                        0x12 // dec. 18
#define DALI_COMMAND_GO_TO_SCENE_3                        0x13 // dec. 19
#define DALI_COMMAND_GO_TO_SCENE_4                        0x14 // dec. 20
#define DALI_COMMAND_GO_TO_SCENE_5                        0x15 // dec. 21
#define DALI_COMMAND_GO_TO_SCENE_6                        0x16 // dec. 22
#define DALI_COMMAND_GO_TO_SCENE_7                        0x17 // dec. 23
#define DALI_COMMAND_GO_TO_SCENE_8                        0x18 // dec. 24
#define DALI_COMMAND_GO_TO_SCENE_9                        0x19 // dec. 25
#define DALI_COMMAND_GO_TO_SCENE_10                       0x1A // dec. 26
#define DALI_COMMAND_GO_TO_SCENE_11                       0x1B // dec. 27
#define DALI_COMMAND_GO_TO_SCENE_12                       0x1C // dec. 28
#define DALI_COMMAND_GO_TO_SCENE_13                       0x1D // dec. 29
#define DALI_COMMAND_GO_TO_SCENE_14                       0x1E // dec. 30
#define DALI_COMMAND_GO_TO_SCENE_15                       0x1F // dec. 31
#define DALI_COMMAND_RESET                                0x20 // dec. 32
#define DALI_COMMAND_STORE_ACTUAL_LEVEL                   0x21 // dec. 33
// reserved
#define DALI_COMMAND_STORE_DTR_AS_MAX_LEVEL               0x2A // dec. 42
#define DALI_COMMAND_STORE_DTR_AS_MIN_LEVEL               0x2B // dec. 43
#define DALI_COMMAND_STORE_DTR_AS_SYSTEM_FAILURE_LEVEL    0x2C // dec. 44
#define DALI_COMMAND_STORE_DTR_AS_POWER_ON_LEVEL          0x2D // dec. 45
#define DALI_COMMAND_STORE_DTR_AS_FADE_TIME               0x2E // dec. 46
#define DALI_COMMAND_STORE_DTR_AS_FADE_RATE               0x2F // dec. 47
// reserved
#define DALI_COMMAND_STORE_DTR_AS_SCENE_0                 0x40 // dec. 64
#define DALI_COMMAND_STORE_DTR_AS_SCENE_1                 0x41 // dec. 65
#define DALI_COMMAND_STORE_DTR_AS_SCENE_2                 0x42 // dec. 66
#define DALI_COMMAND_STORE_DTR_AS_SCENE_3                 0x43 // dec. 67
#define DALI_COMMAND_STORE_DTR_AS_SCENE_4                 0x44 // dec. 68
#define DALI_COMMAND_STORE_DTR_AS_SCENE_5                 0x45 // dec. 69
#define DALI_COMMAND_STORE_DTR_AS_SCENE_6                 0x46 // dec. 70
#define DALI_COMMAND_STORE_DTR_AS_SCENE_7                 0x47 // dec. 71
#define DALI_COMMAND_STORE_DTR_AS_SCENE_8                 0x48 // dec. 72
#define DALI_COMMAND_STORE_DTR_AS_SCENE_9                 0x49 // dec. 73
#define DALI_COMMAND_STORE_DTR_AS_SCENE_10                0x4A // dec. 74
#define DALI_COMMAND_STORE_DTR_AS_SCENE_11                0x4B // dec. 75
#define DALI_COMMAND_STORE_DTR_AS_SCENE_12                0x4C // dec. 76
#define DALI_COMMAND_STORE_DTR_AS_SCENE_13                0x4D // dec. 77
#define DALI_COMMAND_STORE_DTR_AS_SCENE_14                0x4E // dec. 78
#define DALI_COMMAND_STORE_DTR_AS_SCENE_15                0x4F // dec. 79
#define DALI_COMMAND_REMOVE_FROM_SCENE_0                  0x50 // dec. 80
#define DALI_COMMAND_REMOVE_FROM_SCENE_1                  0x51 // dec. 81
#define DALI_COMMAND_REMOVE_FROM_SCENE_2                  0x52 // dec. 82
#define DALI_COMMAND_REMOVE_FROM_SCENE_3                  0x53 // dec. 83
#define DALI_COMMAND_REMOVE_FROM_SCENE_4                  0x54 // dec. 84
#define DALI_COMMAND_REMOVE_FROM_SCENE_5                  0x55 // dec. 85
#define DALI_COMMAND_REMOVE_FROM_SCENE_6                  0x56 // dec. 86
#define DALI_COMMAND_REMOVE_FROM_SCENE_7                  0x57 // dec. 87
#define DALI_COMMAND_REMOVE_FROM_SCENE_8                  0x58 // dec. 88
#define DALI_COMMAND_REMOVE_FROM_SCENE_9                  0x59 // dec. 89
#define DALI_COMMAND_REMOVE_FROM_SCENE_10                 0x5A // dec. 90
#define DALI_COMMAND_REMOVE_FROM_SCENE_11                 0x5B // dec. 91
#define DALI_COMMAND_REMOVE_FROM_SCENE_12                 0x5C // dec. 92
#define DALI_COMMAND_REMOVE_FROM_SCENE_13                 0x5D // dec. 93
#define DALI_COMMAND_REMOVE_FROM_SCENE_14                 0x5E // dec. 94
#define DALI_COMMAND_REMOVE_FROM_SCENE_15                 0x5F // dec. 95
#define DALI_COMMAND_ADD_TO_GROUP_0                       0x60 // dec. 96
#define DALI_COMMAND_ADD_TO_GROUP_1                       0x61 // dec. 97
#define DALI_COMMAND_ADD_TO_GROUP_2                       0x62 // dec. 98
#define DALI_COMMAND_ADD_TO_GROUP_3                       0x63 // dec. 99
#define DALI_COMMAND_ADD_TO_GROUP_4                       0x64 // dec. 100
#define DALI_COMMAND_ADD_TO_GROUP_5                       0x65 // dec. 101
#define DALI_COMMAND_ADD_TO_GROUP_6                       0x66 // dec. 102
#define DALI_COMMAND_ADD_TO_GROUP_7                       0x67 // dec. 103
#define DALI_COMMAND_ADD_TO_GROUP_8                       0x68 // dec. 104
#define DALI_COMMAND_ADD_TO_GROUP_9                       0x69 // dec. 105
#define DALI_COMMAND_ADD_TO_GROUP_10                      0x6A // dec. 106
#define DALI_COMMAND_ADD_TO_GROUP_11                      0x6B // dec. 107
#define DALI_COMMAND_ADD_TO_GROUP_12                      0x6C // dec. 108
#define DALI_COMMAND_ADD_TO_GROUP_13                      0x6D // dec. 109
#define DALI_COMMAND_ADD_TO_GROUP_14                      0x6E // dec. 110
#define DALI_COMMAND_ADD_TO_GROUP_15                      0x6F // dec. 111
#define DALI_COMMAND_REMOVE_FROM_GROUP_0                  0x70 // dec. 112
#define DALI_COMMAND_REMOVE_FROM_GROUP_1                  0x71 // dec. 113
#define DALI_COMMAND_REMOVE_FROM_GROUP_2                  0x72 // dec. 114
#define DALI_COMMAND_REMOVE_FROM_GROUP_3                  0x73 // dec. 115
#define DALI_COMMAND_REMOVE_FROM_GROUP_4                  0x74 // dec. 116
#define DALI_COMMAND_REMOVE_FROM_GROUP_5                  0x75 // dec. 117
#define DALI_COMMAND_REMOVE_FROM_GROUP_6                  0x76 // dec. 118
#define DALI_COMMAND_REMOVE_FROM_GROUP_7                  0x77 // dec. 119
#define DALI_COMMAND_REMOVE_FROM_GROUP_8                  0x78 // dec. 120
#define DALI_COMMAND_REMOVE_FROM_GROUP_9                  0x79 // dec. 121
#define DALI_COMMAND_REMOVE_FROM_GROUP_10                 0x7A // dec. 122
#define DALI_COMMAND_REMOVE_FROM_GROUP_11                 0x7B // dec. 123
#define DALI_COMMAND_REMOVE_FROM_GROUP_12                 0x7C // dec. 124
#define DALI_COMMAND_REMOVE_FROM_GROUP_13                 0x7D // dec. 125
#define DALI_COMMAND_REMOVE_FROM_GROUP_14                 0x7E // dec. 126
#define DALI_COMMAND_REMOVE_FROM_GROUP_15                 0x7F // dec. 127
#define DALI_COMMAND_STORE_DTR_AS_SHORT_ADDRESS           0x80 // dec. 128
#define DALI_COMMAND_ENABLE_WRITE_MEMORY                  0x81 // dec. 129
// reserved
#define DALI_COMMAND_QUERY_STATUS                         0x90 // dec. 144
#define DALI_COMMAND_QUERY_CONTROL_GEAR                   0x91 // dec. 145
#define DALI_COMMAND_QUERY_LAMP_FAILURE                   0x92 // dec. 146
#define DALI_COMMAND_QUERY_LAMP_POWER_ON                  0x93 // dec. 147
#define DALI_COMMAND_QUERY_LIMIT_ERROR                    0x94 // dec. 148
#define DALI_COMMAND_QUERY_RESET_STATE                    0x95 // dec. 149
#define DALI_COMMAND_QUERY_MISSING_SHORT_ADDRESS          0x96 // dec. 150
#define DALI_COMMAND_QUERY_VERSION                        0x97 // dec. 151
#define DALI_COMMAND_QUERY_CONTENT_DTR                    0x98 // dec. 152
#define DALI_COMMAND_QUERY_DEVICE_TYPE                    0x99 // dec. 153
#define DALI_COMMAND_QUERY_PHYSICAL_MINIMUM_LEVEL         0x9A // dec. 154
#define DALI_COMMAND_QUERY_POWER_FAILURE                  0x9B // dec. 155
#define DALI_COMMAND_QUERY_CONTENT_DTR1                   0x9C // dec. 156
#define DALI_COMMAND_QUERY_CONTENT_DTR2                   0x9D // dec. 157
// reserved
#define DALI_COMMAND_QUERY_ACTUAL_LEVEL                   0xA0 // dec. 160
#define DALI_COMMAND_QUERY_MAX_LEVEL                      0xA1 // dec. 161
#define DALI_COMMAND_QUERY_MIN_LEVEL                      0xA2 // dec. 162
#define DALI_COMMAND_QUERY_POWER_ON_LEVEL                 0xA3 // dec. 163
#define DALI_COMMAND_QUERY_SYSTEM_FAILURE_LEVEL           0xA4 // dec. 164
#define DALI_COMMAND_QUERY_FADE_TIME_FADE_RATE            0xA5 // dec. 165
// reserved
#define DALI_COMMAND_QUERY_SCENE_LEVEL_0                  0xB0 // dec. 176
#define DALI_COMMAND_QUERY_SCENE_LEVEL_1                  0xB1 // dec. 177
#define DALI_COMMAND_QUERY_SCENE_LEVEL_2                  0xB2 // dec. 178
#define DALI_COMMAND_QUERY_SCENE_LEVEL_3                  0xB3 // dec. 179
#define DALI_COMMAND_QUERY_SCENE_LEVEL_4                  0xB4 // dec. 180
#define DALI_COMMAND_QUERY_SCENE_LEVEL_5                  0xB5 // dec. 181
#define DALI_COMMAND_QUERY_SCENE_LEVEL_6                  0xB6 // dec. 182
#define DALI_COMMAND_QUERY_SCENE_LEVEL_7                  0xB7 // dec. 183
#define DALI_COMMAND_QUERY_SCENE_LEVEL_8                  0xB8 // dec. 184
#define DALI_COMMAND_QUERY_SCENE_LEVEL_9                  0xB9 // dec. 185
#define DALI_COMMAND_QUERY_SCENE_LEVEL_10                 0xBA // dec. 186
#define DALI_COMMAND_QUERY_SCENE_LEVEL_11                 0xBB // dec. 187
#define DALI_COMMAND_QUERY_SCENE_LEVEL_12                 0xBC // dec. 188
#define DALI_COMMAND_QUERY_SCENE_LEVEL_13                 0xBD // dec. 189
#define DALI_COMMAND_QUERY_SCENE_LEVEL_14                 0xBE // dec. 190
#define DALI_COMMAND_QUERY_SCENE_LEVEL_15                 0xBF // dec. 191
#define DALI_COMMAND_QUERY_GROUPS_0_7                     0xC0 // dec. 192
#define DALI_COMMAND_QUERY_GROUPS_8_15                    0xC1 // dec. 193
#define DALI_COMMAND_QUERY_RANDOM_ADDRESS_H               0xC2 // dec. 194
#define DALI_COMMAND_QUERY_RANDOM_ADDRESS_M               0xC3 // dec. 195
#define DALI_COMMAND_QUERY_RANDOM_ADDRESS_L               0xC4 // dec. 196
#define DALI_COMMAND_READ_MEMORY_LOCATION                 0xC5 // dec. 197
// reserved
#define DALI_COMMAND_QUERY_EXTENDED_VERSION_NUMBER        0xFF // dec. 255

#define DALI_SPECIAL_COMMAND_TERMINATE                    0xA1 // bin. 1010 0001 0000 0000
#define DALI_SPECIAL_COMMAND_DATA_TRANSFER_REGISTER       0xA3 // bin. 1010 0011 XXXX XXXX
#define DALI_SPECIAL_COMMAND_INITIALISE                   0xA5 // bin. 1010 0101 XXXX XXXX
#define DALI_SPECIAL_COMMAND_RANDOMISE                    0xA7 // bin. 1010 0111 0000 0000
#define DALI_SPECIAL_COMMAND_COMPARE                      0xA9 // bin. 1010 1001 0000 0000
#define DALI_SPECIAL_COMMAND_WITHDRAW                     0xAB // bin. 1010 1011 0000 0000
#define DALI_SPECIAL_COMMAND_SEARCHADDRH                  0xB1 // bin. 1011 0001 HHHH HHHH
#define DALI_SPECIAL_COMMAND_SEARCHADDRM                  0xB3 // bin. 1011 0011 MMMM MMMM
#define DALI_SPECIAL_COMMAND_SEARCHADDRL                  0xB5 // bin. 1011 0101 LLLL LLLL
#define DALI_SPECIAL_COMMAND_PROGRAM_SHORT_ADDRESS        0xB7 // bin. 1011 0111 AAAA AAA1
#define DALI_SPECIAL_COMMAND_VERIFY_SHORT_ADDRESS         0xB9 // bin. 1011 1001 AAAA AAA1
#define DALI_SPECIAL_COMMAND_QUERY_SHORT_ADDRESS          0xBB // bin. 1011 1011 0000 0000
#define DALI_SPECIAL_COMMAND_PHYSICAL_SELECTION           0xBD // bin. 1011 1101 0000 0000
// reserved
#define DALI_SPECIAL_COMMAND_ENABLE_DEVICE_TYPE_X         0xC1 // bin. 1100 0001 XXXX XXXX
#define DALI_SPECIAL_COMMAND_DATA_TRANSFER_REGISTER_1     0xC3 // bin. 1100 0011 XXXX XXXX
#define DALI_SPECIAL_COMMAND_DATA_TRANSFER_REGISTER_2     0xC5 // bin. 1100 0101 XXXX XXXX
#define DALI_SPECIAL_COMMAND_WRITE_MEMORY_LOCATION        0xC7 // bin. 1100 0111 XXXX XXXX
// reserved

#endif // __DALI_COMMANDS_H__
