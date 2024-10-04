/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_DRUID and SPELLFAMILY_GENERIC spells used by druid players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dru_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellInfo.h"
#include "Unit.h"
#include "SpellAuraEffects.h"


enum PaladinSpells
{
    SPELL_CRUSADER_STRIKE                     = 35395,
    SPELL_CRUSADER_STRIKE_DEBUFF              = 204024,

    SPELL_JUDGMENT                            = 20271,
    SPELL_JUDGMENT_OF_LIGHT                   = 20185,
    SPELL_JUDGMENT_OF_LIGHT_HEAL              = 20267,
    SPELL_JUDGMENT_OF_WISDOM                  = 20186,
    SPELL_JUDGMENT_OF_WISDOM_MANA_RESTORE     = 20268,
    SPELL_JUDGMENT_OF_JUSTICE                 = 20184,
    SPELL_JUDGMENT_OF_JUSTICE_DEBUFF          = 20271,

    SPELL_SEAL_OF_TRUTH                       = 31801,
    SPELL_SEAL_OF_TRUTH_AURA                  = 20217,

    SPELL_SEAL_OF_LIGHT                       = 20165,
    SPELL_SEAL_OF_LIGHT_AURA                  = 20165,
    SPELL_SEAL_OF_LIGHT_HEAL                  = 20267,

    SPELL_SEAL_OF_JUSTICE                     = 20164,
    SPELL_SEAL_OF_JUSTICE_AURA                = 20164,
    SPELL_SEAL_OF_JUSTICE_EFFECT              = 204301,

    SPELL_SEAL_OF_VENGEANCE                   = 31803,
    SPELL_SEAL_OF_VENGEANCE_AURA              = 31803,
    SPELL_SEAL_OF_VENGEANCE_DOT               = 31803,

    SPELL_SEAL_OF_RIGHTEOUSNESS               = 21084,
    SPELL_SEAL_OF_RIGHTEOUSNESS_AURA          = 21084,

    SPELL_SEAL_OF_COMMAND                     = 20375,
    SPELL_SEAL_OF_COMMAND_AURA                = 20375,
    SPELL_SEAL_OF_COMMAND_PROC                = 20424,

    SPELL_SEAL_OF_WISDOM                      = 20166,
    SPELL_SEAL_OF_WISDOM_AURA                 = 20166,
    SPELL_SEAL_OF_WISDOM_MANA_RESTORE         = 20167,

    SPELL_DIVINE_SHIELD                       = 642,
    SPELL_DIVINE_SHIELD_AURA                  = 642,

    SPELL_DIVINE_PROTECTION                   = 498,
    SPELL_DIVINE_PROTECTION_AURA              = 498,

    SPELL_DIVINE_PLEA                         = 54428,
    SPELL_DIVINE_PLEA_MANA_RESTORE            = 54428,

    SPELL_RIGHTEOUS_FURY                      = 25780,
    SPELL_RIGHTEOUS_FURY_AURA                 = 25780,

    SPELL_CLEANSE                             = 4987,
    SPELL_PURIFY                              = 1152,
    SPELL_REDEMPTION                          = 7328,

    SPELL_DIVINE_STORM                        = 53385,
    SPELL_DIVINE_STORM_DAMAGE                 = 53385,

    SPELL_CONSECRATION                        = 26573,
    SPELL_CONSECRATION_AURA                   = 26573,

    SPELL_HOLY_WRATH                          = 2812,
    SPELL_HOLY_WRATH_DAMAGE                   = 2812,

    SPELL_EXORCISM                            = 879,
    SPELL_EXORCISM_DAMAGE                     = 879,

    SPELL_HOLY_LIGHT                          = 635,
    SPELL_HOLY_LIGHT_HEAL                     = 639,

    SPELL_FLASH_OF_LIGHT                      = 19750,
    SPELL_FLASH_OF_LIGHT_HEAL                 = 19751,

    SPELL_SUMMON_WARHORSE                     = 13819,
    SPELL_SUMMON_WARHORSE_AURA                = 34769,

    SPELL_SUMMON_CHARGER                      = 23214,
    SPELL_SUMMON_CHARGER_AURA                 = 34767,
};


// Define the Paladin namespace to encapsulate all Paladin spell scripts
namespace Scripts::Spells::Paladin
{
    // Crusader Strike
    class spell_pal_crusader_strike : public SpellScript
    {
        PrepareSpellScript(spell_pal_crusader_strike);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_CRUSADER_STRIKE_DEBUFF, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_crusader_strike::HandleOnHit);
        }
    };

    // Judgment of Light
    class spell_pal_judgment_of_light : public SpellScript
    {
        PrepareSpellScript(spell_pal_judgment_of_light);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_JUDGMENT_OF_LIGHT_HEAL, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_judgment_of_light::HandleOnHit);
        }
    };

    // Seal of Truth
    class spell_pal_seal_of_truth : public SpellScript
    {
        PrepareSpellScript(spell_pal_seal_of_truth);

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_SEAL_OF_TRUTH_AURA, true);
        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_pal_seal_of_truth::HandleAfterCast);
        }
    };

    // Divine Storm
    class spell_pal_divine_storm : public SpellScript
    {
        PrepareSpellScript(spell_pal_divine_storm);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_DIVINE_STORM_DAMAGE, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_divine_storm::HandleOnHit);
        }
    };

    // Consecration
    class spell_pal_consecration : public SpellScript
    {
        PrepareSpellScript(spell_pal_consecration);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_CONSECRATION_AURA, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_consecration::HandleOnCast);
        }
    };

    // Holy Wrath
    class spell_pal_holy_wrath : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_wrath);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_HOLY_WRATH_DAMAGE, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_holy_wrath::HandleOnHit);
        }
    };

    // Exorcism
    class spell_pal_exorcism : public SpellScript
    {
        PrepareSpellScript(spell_pal_exorcism);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_EXORCISM_DAMAGE, true);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pal_exorcism::HandleOnHit);
        }
    };

    // Holy Light
    class spell_pal_holy_light : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_light);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            target->CastSpell(target, SPELL_HOLY_LIGHT_HEAL, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_holy_light::HandleOnCast);
        }
    };

    // Flash of Light
    class spell_pal_flash_of_light : public SpellScript
    {
        PrepareSpellScript(spell_pal_flash_of_light);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            target->CastSpell(target, SPELL_FLASH_OF_LIGHT_HEAL, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_flash_of_light::HandleOnCast);
        }
    };

    // Summon Warhorse
    class spell_pal_summon_warhorse : public SpellScript
    {
        PrepareSpellScript(spell_pal_summon_warhorse);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_SUMMON_WARHORSE_AURA, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_summon_warhorse::HandleOnCast);
        }
    };

    // Summon Charger
    class spell_pal_summon_charger : public SpellScript
    {
        PrepareSpellScript(spell_pal_summon_charger);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_SUMMON_CHARGER_AURA, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_summon_charger::HandleOnCast);
        }
    };

    // Divine Shield
    class spell_pal_divine_shield : public SpellScript
    {
        PrepareSpellScript(spell_pal_divine_shield);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            caster->CastSpell(caster, SPELL_DIVINE_SHIELD_AURA, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_divine_shield::HandleOnCast);
        }
    };

    // Cleanse
    class spell_pal_cleanse : public SpellScript
    {
        PrepareSpellScript(spell_pal_cleanse);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_CLEANSE, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_cleanse::HandleOnCast);
        }
    };
}

// Function to register all Paladin spell scripts
void AddSC_paladin_spell_scripts()
{
    using namespace Scripts::Spells::Paladin;

    RegisterSpellScript(spell_pal_crusader_strike);
    RegisterSpellScript(spell_pal_judgment_of_light);
    RegisterSpellScript(spell_pal_seal_of_truth);
    RegisterSpellScript(spell_pal_divine_storm);
    RegisterSpellScript(spell_pal_consecration);
    RegisterSpellScript(spell_pal_holy_wrath);
    RegisterSpellScript(spell_pal_exorcism);
    RegisterSpellScript(spell_pal_holy_light);
    RegisterSpellScript(spell_pal_flash_of_light);
    RegisterSpellScript(spell_pal_summon_warhorse);
    RegisterSpellScript(spell_pal_summon_charger);
    RegisterSpellScript(spell_pal_divine_shield);
    RegisterSpellScript(spell_pal_cleanse);
}
