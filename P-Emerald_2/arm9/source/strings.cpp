/*
Pok�mon Emerald 2 Version
------------------------------

file        : strings.cpp
author      : Philip Wellnitz
description :

Copyright (C) 2012 - 2018
Philip Wellnitz

This file is part of Pok�mon Emerald 2 Version.

Pok�mon Emerald 2 Version is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Pok�mon Emerald 2 Version is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Pok�mon Emerald 2 Version.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "defines.h"
#include "saveGame.h"

const char* const SAVE::CHAPTER_NAMES[ 2 * MAX_CHAPTERS ][ LANGUAGES ] = {
    {"Prologue", "Prolog"},     {"I Choose You!", "Ich W�hle Dich!"},
    {"Chapter 1", "Kapitel 1"}, {"(tba)", "(tba)"},
    {"Chapter 2", "Kapitel 2"}, {"(tba)", "(tba)"},
    {"Chapter 3", "Kapitel 3"}, {"(tba)", "(tba)"},
    {"Chapter 4", "Kapitel 4"}, {"(tba)", "(tba)"},

    {"Chapter 5", "Kapitel 5"}, {"(tba)", "(tba)"},
    {"Chapter 6", "Kapitel 6"}, {"(tba)", "(tba)"},
    {"Chapter 7", "Kapitel 7"}, {"(tba)", "(tba)"},
    {"Chapter 8", "Kapitel 8"}, {"(tba)", "(tba)"},
    {"Chapter 9", "Kapitel 9"}, {"(tba)", "(tba)"},

    {"Final", "Letztes"},       {"Pok�mon", "Pok�mon"},
    {"Epilogue", "Epilog"},     {"Life Goes On", "Das Leben Geht Weiter"},
};

const char* SAVE::EPISODE_NAMES[ LANGUAGES ][ MAX_SPECIAL_EPISODES ]
    = {{"Dev's Heaven"}, {"Dev's Heaven"}};

const char* LANGUAGE_NAMES[ LANGUAGES ] = {"English", "Deutsch"};

const char* const STRINGS[ MAX_STRINGS ][ LANGUAGES ] = {
    {"No data.", "Keine Daten."},
    {"Faraway Place", "Entfernter Ort"},
    {"Unknown", "Unbekannt"},
    {"%s\nUse %s?", "%s\nM�chtest du %s nutzen?"},
    {"The repel wore off.", "Der Schutz ist aufgebraucht."},

    {"Just an old Pok� Ball�", "Doch nur ein alter Pok�ball�"},
    {"You fished a Pok�mon!", "Du hast ein Pok�mon geangelt!"},
    {"Map border.\nReturn, or you\nwill get lost!",
     "Ende der Kartendaten.\nKehr um, sonst\nverirrst du dich!"},
    {"\nSomething's on the hook!", "\nDa ist etwas am Haken!"},
    {"It disappeared�", "Es ist entkommen�"},

    // 10

    {"%s%s used %s![A]", "%s%s setzt\n%s ein![A]"},
    {"Items", "Items"},
    {"Medicine", "Medizin"},
    {"TM/HM", "TM/VM"},
    {"Berries", "Beeren"},

    {"Key Items", "Basis-Items"},
    {"Firmness: %s", "G�te: %s"},
    {"Hard", "Hart"},
    {"Soft", "Weich"},
    {"Super hard", "Steinhart"},

    // 20

    {"Super soft", "Sehr weich"},
    {"Very hard", "Sehr hart"},
    {"Normal", "Normal"},
    {"Size:%4.1fcm", "Gr��e:%4.1fcm"},
    {"Spicy", "Scharf"},

    {"Dry", "Trocken"},
    {"Sweet", "S��"},
    {"Bitter", "Bitter"},
    {"Sour", "Sauer"},
    {"Type", "Typ"},

    // 30

    {"Categ.", "Kateg."},
    {"PP", "AP"},
    {"Strength", "St�rke"},
    {"Accuracy", "Genauigkeit"},
    {"Egg", "Ei"},

    {"Already\nlearned", "Bereits\nerlernt"},
    {"Possible", "Erlernbar"},
    {"Not\npossible", "Nicht\nerlernbar"},
    {"Level %3d\n%3d/%3d HP", "Level %3d\n%3d/%3d KP"},
    {"Level %3d\n Fainted", "Level %3d\n Besiegt"},

    // 40

    {"Possible", "M�glich"},
    {"Not\npossible", "Nicht\nm�glich"},
    {"No item", "Kein Item"},
    {"No items", "Keine Items"},
    {"Give", "Geben"},

    {"Apply", "Anwenden"},
    {"Register", "Registrieren"},
    {"Use", "Einsetzen"},
    {"Trash", "Wegwerfen"},
    {"Select a move!", "Welche Attacke?"},

    // 50

    {"Used %s on %s.", "%s auf %s angewendet."},
    {"%s is evolving�", "%s entwickelt sich�"},
    {"�and became a(n)\n%s!", "�und wurde zu einem\n%s!"},
    {"It would be\nwasted�", "Es w�rde keine\nWirkung haben�"},
    {"%s holds\n%s already.\nSwap the items?",
     "%s tr�gt bereits\ndas Item %s.\nSollen die Items getauscht werden?"}, // TODO

    {"You can't choose\nthis item.", "Dieses Item kann nicht\nausgew�hlt werden."},
    {"Choose %s?", "%s ausw�hlen?"},
    {"What do you want to do\nwith %s?", "Was tun mit %s?"},
    {"You can't use\nthat right now.", "Das kann jetzt nicht\neingesetzt werden."},
    {"Pok�mon team", "Pok�mon-Team"},

    // 60

    {"Cache", "Zwischenablage"},
    {"All boxes", "Alle Boxen"},
    {"New name for box �%s�", "Name f�r Box �%s�"},
    {"Repel activated.", "Schutz eingesetzt."},
    {"Super Repel activated.", "Superschutz eingesetzt."},

    {"Max Repel activated.", "Top-Schutz eingesetzt."},
    {"Exp. All deactivated.", "EP-Teiler ausgeschaltet."},
    {"Exp. All activated.", "EP-Teiler eingeschaltet."},
    {"Coins: %lu.", "M�nzen: %lu."},
    {"BP: %lu.", "Kampfpunkte: %lu."},

    // 70

    {"         TOUCH TO START", "     BER\x9A"
                                "HRE, UM ZU STARTEN"},
    {"Continue", "Weiter"},
    {"New Game", "Neues Spiel"},
    {"Special Episodes", "Spezialepisoden"},
    {"Import Save", "Spiel-Import"},

    {"Continue your adventure", "Setze dein Abenteuer fort"},
    {"Start a new adventure", "Starte ein neues Abenteuer"},
    {"Learn your companion's stories", "Erfahre mehr �ber deine Begleiter"},
    {"Revive myths of old", "Setze alte Abenteuer fort"},
    {"This slot contains a saved game.\nOverride it?",
     "Es existiert bereits ein Spielstand.\nSoll dieser �berschrieben werden?"},

    // 80

    {"Yes", "Ja"},
    {"No", "Nein"},
    {"(empty)", "(leer)"},
    {"Transfer", "Transfer"},
    {"Special", "Spezial"},

    {"The language is currently\nset to �English�.\nChange the language setting?",
     "Die eingestellte Sprache\nist �Deutsch�.\nSprache �ndern?"},
    {"into the %s bag.`", "%s-Tasche verstaut.`"},
    {"Stored %s %s", "%s %s in der"},
    {"Stored %s", "%s in der"},
    {"Stored %3d %s", "%3d %s in der"},

    // 90

    {"The scent vanished�", "Der Duft verstrich wirkungslos�"},
    {"Pok�Nav", "Pok�Nav"},
    {" Would you like to\n save your progress?\n", " M�chtest du deinen\n Fortschritt sichern?\n"},
    {"Save?\nFrom an emulator?!", "Speichern?\nIn einem Emulator?!"},
    {"Saved successfully!", "Speichern erfolgreich!"},

    {"An error occured.\nProgress not saved.", "Es trat ein Fehler auf\nSpiel nicht gesichert."},
    {"No %s available.\nRemove the icon?",
     "Kein Exemplar des Items\n%s vorhanden.\nIcon entfernen?"},
    {"Recently used items\nwill appear here.", "Hier erscheinen zuletzt\neingesetzte Items."},
    {"You may register an\nitem to the button Y.", "Du kannst ein Item\nauf Y registrieren."},
    {"%s used %s!", "%s setzt %s\nein!"},

    // 100

    {"You can't use this\nmove right now.", "Diese Attacke kann jetzt\nnicht eingesetzt werden."},
    {"Stored %s\nfrom %s.", "%s von %s\nim Beutel verstaut."},
    {"%s already\nknows %s!", "%s beherrscht\n%s bereits!"},
    {"%s learned\n%s!", "%s erlernt\n%s!"},
    {"%s already\nknows 4 moves.\nForget a move?",
     "%s beherrscht\nbereits 4 Attacken.\nSoll eine verlernt werden?"},

    {"Select a move!", "Welche Attacke?"},
    {"%s can't\nforget %s!", "%s kann\n%s nicht vergessen!"},
    {"%s can't\nlearn %s!", "%s kann\n%s nicht erlernen!"},
    {"%hhu badges", "%hhu Orden"},
    {"Pick a language", "W�hle eine Sprache"},

    // 110

    {"Choose an episode", "W�hle eine Speizalepisode"},
    {"Welcome to Special Episode 0:\nDeveloper's Heaven.",
     "Willkommen zur Spezialepisode 0:\nDeveloper's Heaven"},
    {"In this episode, you will gain\nthe mighty powers of the\ndev himself.",
     "In dieser Episode erh�ltst du\ndie F�higkeiten des Entwicklers."},
    {"Do whatever you want.", "Mach damit, was immer du m�chtest."},
    {"Do you want to import your\nsave from the GBA game?",
     "M�chtest du deinen Spielstand\nvon dem GBA-Modul auf dem DS\nfortsetzen?"},

    {"Importing a save file will\ncopy all Pok�mon and items\nfrom the GBA game.",
     "Beim Importieren werden alle\nPok�mon und Items vom\nGBA-Modul kopiert."},
    {"Further, you will start at\nthe same position as you\nleft off in the GBA game.",
     "Du wirst das Spiel an der\nselben Stelle wie auf dem\nGBA-Modul fortsetzen."},
    {"No data will be written to\nthe GBA Game Pak.",
     "Es werden keine Daten auf\ndas GBA-Modul geschrieben."},
    {"However, proceed at your\nown risk.",
     "Trotzdem geschieht das\nImportieren auf eigene\nGefahr."},
    {"No compatible cartrige found.\nAborting.",
     "Kein kompatibles GBA-Modul\ngefunden.\nBreche ab."},

    // 120

    {"Proceed?", "Fortfahren?"},
    {"Importing data�", "Lade Spielstand�"},
    {"An error occured.\nAborting.", "Ein Fehler ist aufgetreten.\nKehre zum Hauptmen� zur�ck."},
    {"Completed.", "Abgeschlossen."},
    {"Entries", "Eintr�ge"},

    {"All", "Alle"},
    {"HP", "KP"},
    {"Attack", "Angriff"},
    {"Defense", "Vert"},
    {"Speed", "Initiative"},

    // 130

    {"Sp. Atk", "Sp.-Angr"},
    {"Sp. Def", "Sp.-Vert"},
    {"f. %s", "aus %s"},
    {"female", "weiblich"},
    {"male", "m�nnlich"},

    {"(shining)", "(schillernd)"},
    {"Fainted", "Besiegt"},
    {"Statistics", "Statuswerte"},
    {"Stats at lv.%3i:", "Status auf Lv.%3i:"},
    {"[TRAINER] ([TCLASS]) sent\nout %s![A]", "[TRAINER] ([TCLASS]) schickt\n%s in den Kampf![A]"},

    // 140

    {"Go [OWN%d]![A]", "Los [OWN%d]![A]"},
    {"Do you want to give\na nick name to %s?", "M�chtest du dem %s\neinen Spitznamen geben?"},
    {"Choose a nick name!", "W�hle einen Spitznamen!"},
    {"You are challenged by\n%s %s![END]", "Eine Herausforderung von\n%s %s![END]"},
    {"Frzn", "Eingfr"},

    {"Prlz", "Prlyse"},
    {"Burn", "Verbrng"},
    {"Slp", "Schlaf"},
    {"Psn", "Gift"},
    {"Switch", "Aussenden"},

    // 150

    {"In Battle", "Bereits im Kampf"},
    {"Cannot Battle", "Schon besiegt�"},
    {"To be sent", "Schon ausgew�hlt"},
    {"Eggs can't", "Ein Ei kann"},
    {"battle!", "nicht k�mpfen!"},

    {"Status", "Bericht"},
    {"Moves", "Attacken"},
    {"ATK", "ANG"},
    {"DEF", "VER"},
    {"SAT", "SAN"},

    // 160

    {"SDF", "SVE"},
    {"SPD", "INI"},
    {"What will %s do?", "Was soll %s tun?"},
    {"You got away safely.[A]", "Du bist entkommen.[A]"},
    {"You couldn't escape�[A]", "Flucht gescheitert�[A]"},

    {"Choose a target!", "Welches PKMN angreifen?"},
    {"Choose a Pok�mon.", "Welches Pok�mon?"},
    {"%s gained %lu EXP.[A]", "%s gewinnt %lu E.-Punkte.[A]"},
    {"%s advanced\nto level %d.[A]", "%s erreicht Level %d.[A]"},
    {"The quick claw enabled\n%s%s to go first![A]",
     "%s%s agiert dank\neiner Flinkklaue zuerst![A]"},

    // 170

    {"%s of %s%s applies.[A]", "%s von %s%s wirkt.[A]"},
    {"[TRAINER] ([TCLASS])\nused %s.[A]", "[TRAINER] ([TCLASS]) setzt\n%s ein.[A]"},
    {"It got wasted�[A]", "Es hat keine Wirkung�[A]"},
    {"Used %s.[A]", "%s eingesetzt.[A]"},
    {"%s's data was\nregistred to the Pok� Dex.[A]",
     "Die Daten von %s\nwurden im Pok�Dex gespeichert.[A]"},

    {"%s was sent to\nthe Pok�mon Storage System.[A]",
     "%s wurde an das\nPok�mon-Lagerungssystem\ngeschickt.[A]"},
    {"Box �%s� is full.[A]", "Box �%s� ist voll.[A]"},
    {"%s was deposited\nto Box �%s�.[A]", "%s wurde in\nBox �%s� abgelegt.[A]"},
    {"There is no space left\nfor additional Pok�mon.[A]",
     "Du hast keinen Platz\nf�r weitere Pok�mon.[A]"},
    {"%s was released.[A]", "%s wurde wieder\nfreigelassen.[A]"},

    // 180

    {"FIGHT", "Kampf"},
    {"BAG", "Beutel"},
    {"POK�MON", "Pok�mon"},
    {"RUN", "Flucht"},
    {"Pwr", "Stk"},

    {"Meteor Falls", "Meteorf�lle"}};
