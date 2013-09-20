/*
Copyright (C) 2008-2013 Vana Development Team

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
#pragma once

#include "ConfigFile.h"
#include "IConfig.h"
#include "IPacket.h"
#include "Ip.h"
#include "PacketCreator.h"
#include "PacketReader.h"
#include "Types.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

struct MajorBoss : public IPacketSerializable {
	int16_t attempts;
	vector<int8_t> channels;
	
	MajorBoss() :
		attempts(0)
	{
	}

	void write(PacketCreator &packet) const override {
		packet.add<int16_t>(attempts);
		packet.addVector(channels);
	}
	void read(PacketReader &packet) override {
		attempts = packet.get<int16_t>();
		channels = packet.getVector<int8_t>();
	}
};

struct Rates : public IPacketSerializable {
	int32_t mobExpRate;
	int32_t questExpRate;
	int32_t mobMesoRate;
	int32_t dropRate;

	struct Types {
		static const int32_t MobExpRate = 0x01;
		static const int32_t QuestExpRate = 0x02;
		static const int32_t MobMesoRate = 0x04;
		static const int32_t DropRate = 0x08;
	};

	Rates() :
		mobExpRate(1),
		questExpRate(1),
		mobMesoRate(1),
		dropRate(1)
	{
	}

	void write(PacketCreator &packet) const override {
		packet.add<int32_t>(mobExpRate);
		packet.add<int32_t>(questExpRate);
		packet.add<int32_t>(mobMesoRate);
		packet.add<int32_t>(dropRate);
	}
	void read(PacketReader &packet) override {
		mobExpRate = packet.get<int32_t>();
		questExpRate = packet.get<int32_t>();
		mobMesoRate = packet.get<int32_t>();
		dropRate = packet.get<int32_t>();
	}
};

struct WorldConfig : public IPacketSerializable {
	int8_t ribbon;
	uint8_t maxMultiLevel;
	uint8_t defaultStorageSlots;
	int16_t maxStats;
	int32_t defaultChars;
	int32_t maxChars;
	int32_t maxPlayerLoad;
	int32_t fameTime;
	int32_t fameResetTime;
	size_t maxChannels;
	string eventMsg;
	string scrollingHeader;
	string name;
	Rates rates;
	MajorBoss pianus;
	MajorBoss pap;
	MajorBoss zakum;
	MajorBoss horntail;
	MajorBoss pinkbean;

	WorldConfig() :
		ribbon(0),
		maxMultiLevel(1),
		defaultStorageSlots(4),
		maxStats(999),
		defaultChars(3),
		maxChars(6),
		maxPlayerLoad(100),
		fameTime(30 * 60 * 60),
		fameResetTime(30 * 60 * 60),
		maxChannels(20)
	{
	}

	void write(PacketCreator &packet) const override {
		packet.add<int8_t>(ribbon);
		packet.add<uint8_t>(maxMultiLevel);
		packet.add<uint8_t>(defaultStorageSlots);
		packet.add<int16_t>(maxStats);
		packet.add<int32_t>(defaultChars);
		packet.add<int32_t>(maxChars);
		packet.add<int32_t>(maxPlayerLoad);
		packet.add<int32_t>(maxChannels);
		packet.add<int32_t>(fameTime);
		packet.add<int32_t>(fameResetTime);
		packet.addString(eventMsg);
		packet.addString(scrollingHeader);
		packet.addString(name);
		packet.addClass<Rates>(rates);
		packet.addClass<MajorBoss>(pianus);
		packet.addClass<MajorBoss>(pap);
		packet.addClass<MajorBoss>(zakum);
		packet.addClass<MajorBoss>(horntail);
		packet.addClass<MajorBoss>(pinkbean);
	}
	void read(PacketReader &packet) override {
		ribbon = packet.get<int8_t>();
		maxMultiLevel = packet.get<uint8_t>();
		defaultStorageSlots = packet.get<uint8_t>();
		maxStats = packet.get<int16_t>();
		defaultChars = packet.get<int32_t>();
		maxChars = packet.get<int32_t>();
		maxPlayerLoad = packet.get<int32_t>();
		maxChannels = packet.get<int32_t>();
		fameTime = packet.get<int32_t>();
		fameResetTime = packet.get<int32_t>();
		eventMsg = packet.getString();
		scrollingHeader = packet.getString();
		name = packet.getString();
		rates = packet.getClass<Rates>();
		pianus = packet.getClass<MajorBoss>();
		pap = packet.getClass<MajorBoss>();
		zakum = packet.getClass<MajorBoss>();
		horntail = packet.getClass<MajorBoss>();
		pinkbean = packet.getClass<MajorBoss>();
	}
};

struct LoginConfig : public IConfigReadable<LoginConfig> {
	bool clientEncryption;
	bool clientPing;
	bool serverPing;

	LoginConfig() :
		clientEncryption(true),
		clientPing(true),
		serverPing(true)
	{
	}

	void read(ConfigFile &conf, const string &prefix) override {
		clientEncryption = conf.get<bool>("use_client_encryption");
		clientPing = conf.get<bool>("use_client_ping");
		serverPing = conf.get<bool>("use_inter_ping");
	}
};

struct LogConfig : public IConfigReadable<LogConfig> {
	int32_t destination;
	uint32_t bufferSize;
	string format;
	string timeFormat;
	string file;

	LogConfig() :
		destination(0),
		bufferSize(20)
	{
	}

	void read(ConfigFile &conf, const string &prefix) override {
		const string &fullPrefix = prefix + "_log_";
		destination = conf.get<int32_t>(fullPrefix + "destination");
		bufferSize = conf.get<uint32_t>(fullPrefix + "buffer_size");
		format = conf.getString(fullPrefix + "format");
		file = conf.getString(fullPrefix + "file");
		timeFormat = conf.getString("log_time_format");
	}
};

struct DbConfig : public IConfigReadable<DbConfig> {
	string database;
	string host;
	string username;
	string password;
	port_t port;

	DbConfig() :
		port(0)
	{
	}

	void read(ConfigFile &conf, const string &prefix) override {
		const string &fullPrefix = prefix + "_";
		database = conf.getString(fullPrefix + "database");
		host = conf.getString(fullPrefix + "host");
		username = conf.getString(fullPrefix + "username");
		password = conf.getString(fullPrefix + "password");
		port = conf.get<port_t>(fullPrefix + "port");
	}
};

struct InterServerConfig : public IConfigReadable<InterServerConfig> {
	Ip loginIp;
	port_t port;

	InterServerConfig() :
		loginIp(0),
		port(0)
	{
	}

	void read(ConfigFile &conf, const string &prefix) override {
		loginIp = Ip(Ip::stringToIpv4(conf.getString("login_ip")));
		port = conf.get<port_t>("login_inter_port");
	}
};