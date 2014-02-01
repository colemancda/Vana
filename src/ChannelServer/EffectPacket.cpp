/*
Copyright (C) 2008-2014 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "EffectPacket.hpp"
#include "Maps.hpp"
#include "Player.hpp"
#include "SmsgHeader.hpp"

namespace EffectPacket {

PACKET_IMPL(playMusic, const string_t &music) {
	PacketBuilder builder;
	builder
		.add<header_t>(SMSG_MAP_EFFECT)
		.add<int8_t>(0x06)
		.addString(music);
	return builder;
}

PACKET_IMPL(sendEvent, const string_t &id) {
	PacketBuilder builder;
	// Look in Map.wz/Effect.img to find valid strings
	builder
		.add<header_t>(SMSG_MAP_EFFECT)
		.add<int8_t>(0x03)
		.addString(id);
	return builder;
}

PACKET_IMPL(sendEffect, const string_t &effect) {
	PacketBuilder builder;
	// Look in Map.wz/Obj/Effect.img/quest/ for valid strings
	builder
		.add<header_t>(SMSG_MAP_EFFECT)
		.add<int8_t>(0x02)
		.addString(effect);
	return builder;
}

PACKET_IMPL(playPortalSoundEffect) {
	PacketBuilder builder;
	builder
		.add<header_t>(SMSG_THEATRICS)
		.add<int8_t>(0x07);
	return builder;
}

PACKET_IMPL(sendFieldSound, const string_t &sound) {
	PacketBuilder builder;
	// Look in Sound.wz/Field.img to find valid strings
	builder
		.add<header_t>(SMSG_MAP_EFFECT)
		.add<int8_t>(0x04)
		.addString(sound);
	return builder;
}

PACKET_IMPL(sendMinigameSound, const string_t &sound) {
	PacketBuilder builder;
	// Look in Sound.wz/MiniGame.img to find valid strings
	builder
		.add<header_t>(SMSG_SOUND)
		.addString(sound);
	return builder;
}

SPLIT_PACKET_IMPL(sendMobItemBuffEffect, int32_t playerId, int32_t itemId) {
	SplitPacketBuilder builder;
	PacketBuilder packet;
	packet
		.add<int8_t>(0x0B)
		.add<int32_t>(itemId);

	builder.player
		.add<header_t>(SMSG_THEATRICS)
		.addBuffer(packet);

	builder.map
		.add<header_t>(SMSG_SKILL_SHOW)
		.add<int32_t>(playerId)
		.addBuffer(packet);
	return builder;
}

}