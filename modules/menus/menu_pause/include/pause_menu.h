#include "menu.h"

struct PauseData {
    uint8_t l_ordonSword_idx;
    uint8_t l_masterSword_idx;
    uint8_t l_woodShield_idx;
    uint8_t l_hyShield_idx;
    uint8_t l_tunic_idx;
    uint8_t l_zoraArmor_idx;
    uint8_t l_magicArmor_idx;
    uint8_t l_bombCap_idx;
    uint8_t l_wallet_idx;
    uint8_t l_arrowCap_idx;
    bool l_ebFlag;
    bool l_sbFlag;
    bool l_bsFlag;
    bool l_hsFlag;
    bool l_mdFlag;
    bool l_jsFlag;
    bool l_gsFlag;
};

enum PauseIndex {
    ORDON_SWORD_INDEX,
    MASTER_SWORD_INDEX,
    WOOD_SHIELD_INDEX,
    HYLIAN_SHIELD_INDEX,
    HERO_TUNIC_INDEX,
    ZORA_ARMOR_INDEX,
    MAGIC_ARMOR_INDEX,
    BOMB_CAPACITY_INDEX,
    WALLET_INDEX,
    ARROW_CAPACITY_INDEX,
    ENDING_BLOW_INDEX,
    SHIELD_BASH_INDEX,
    BACKSLICE_INDEX,
    HELM_SPLITTER_INDEX,
    MORTAL_DRAW_INDEX,
    JUMP_STRIKE_INDEX,
    GREAT_SPIN_INDEX
};

class PauseMenu : public Menu {
public:
    PauseMenu(Cursor&, PauseData&);
    virtual ~PauseMenu();
    virtual void draw();

private:
    uint8_t& l_ordonSword_idx;
    uint8_t& l_masterSword_idx;
    uint8_t& l_woodShield_idx;
    uint8_t& l_hyShield_idx;
    uint8_t& l_tunic_idx;
    uint8_t& l_zoraArmor_idx;
    uint8_t& l_magicArmor_idx;
    uint8_t& l_bombCap_idx;
    uint8_t& l_wallet_idx;
    uint8_t& l_arrowCap_idx;
    bool& l_ebFlag;
    bool& l_sbFlag;
    bool& l_bsFlag;
    bool& l_hsFlag;
    bool& l_mdFlag;
    bool& l_jsFlag;
    bool& l_gsFlag;

    Line lines[17];

    void resetIndex();
    void getEquipment();
    void setEquipment();
};