
// Player’s skill, unique to each character:
struct skill_t {
    char* name;
    unsigned int cur_level;
    unsigned int experience;
    char* description;
    int (*execute_skill)(int param1, int param2);
};

typedef struct skill_t skill_t;

// Struct which holds a player's every skill, differentiated by passive and
// active.
// When not holding a skill, each space in the passive or active skill lists is
// defined as NULL.
struct allskills_t {
    skill_t** active_skills;
    unsigned int cur_num_active;
    unsigned int max_num_active;
    skill_t** passive_skills;
    unsigned int cur_num_passive;
    unsigned int max_num_passive;
};

typedef struct allskills_t allskills_t;

// Creates a new skill when given all of the parameters needed for a skill.
// Returns a fully malloc'd skill.
skill_t* new_skill(char* name, unsigned int cur_level, unsigned int experience,
                   char* description, int (*given_skill)(int, int));

// Frees a skill.
// Returns an error code.
int free_skill(skill_t* skill);

// Creates a new skill list, initially mallocing space for 5 active and 5
// passive skills.
// Returns the malloc'd list.
allskills_t* create_skill_list();

// Frees all skills in the skill list.
// Returns an error code.
int free_all_skills(allskills_t* list);

// Pushes an active skill into the active skill list.
// Returns an error code.
int push_active_skill(allskills_t* list, skill_t* skill);

// Pushes a passive skill into the passive skill list.
// Returns an error code.
int push_passive_skill(allskills_t* list, skill_t* skill);

// Pops an active skill from the active skill list.
// Returns 1 when there wasn't a skill to be found, else, 0.
int pop_active_skill(allskills_t* list, skill_t* skill);

// Pops a passive skill from the passive skill list.
// Returns 1 when there wasn't a skill to be found, else, 0.
int pop_passive_skill(allskills_t* list, skill_t* skill);

// Tests to see if there is an active skill inside of the current skill list.
// Returns the location of the skill in the active_skill list  when the skill
// was found, else, -1.
int has_active_skill(allskills_t* list, skill_t* skill);

// Tests to see if there is a passive skill inside of the current skill list.
// Returns the location of the skill in the passive_skill list  when the skill
// was found, else, -1.
int has_passive_skill(allskills_t* list, skill_t* skill);

// Functions needed in regards to this:
// 5) Activate passive skills — Activates all passive skills in the list


// // Overall skill tree, shared by every player:
// struct tree_skill {
//     //Skill name // Name of the skill
//     //Dependencies // Which skills are required to unlock this skill
//     //Skills unlocked after// Skills that have this struct’s skill as a
//     //dependencies.
//     //Max level // Max level that this skill can be.
//
// };

// Functions needed in regards to this:
// 1) find_requirements — A player calls this when they want to know how to
// get a skill.
// 2) find_unlockables — A player calls this when they want to know
// what they can get after they unlock this skill.
