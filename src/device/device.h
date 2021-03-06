/*
 * Copyright (c) 2012-2017 Daniele Bartolini and individual contributors.
 * License: https://github.com/dbartolini/crown/blob/master/LICENSE
 */

#pragma once

#include "config.h"
#include "core/containers/types.h"
#include "core/filesystem/types.h"
#include "core/memory/allocator.h"
#include "core/memory/linear_allocator.h"
#include "core/strings/string_id.h"
#include "core/types.h"
#include "device/boot_config.h"
#include "device/console_server.h"
#include "device/device_options.h"
#include "device/display.h"
#include "device/input_types.h"
#include "device/window.h"
#include "lua/types.h"
#include "resource/types.h"
#include "resource/types.h"
#include "world/types.h"

/// @defgroup Device Device
namespace crown
{
struct BgfxAllocator;
struct BgfxCallback;

/// This is the place where to look for accessing all of
/// the engine subsystems and related stuff.
///
/// @ingroup Device
struct Device
{
	LinearAllocator _allocator;

	const DeviceOptions& _device_options;
	BootConfig _boot_config;
	ConsoleServer* _console_server;
	Filesystem* _data_filesystem;
	File* _last_log;
	ResourceLoader* _resource_loader;
	ResourceManager* _resource_manager;
	BgfxAllocator* _bgfx_allocator;
	BgfxCallback* _bgfx_callback;
	ShaderManager* _shader_manager;
	MaterialManager* _material_manager;
	InputManager* _input_manager;
	UnitManager* _unit_manager;
	LuaEnvironment* _lua_environment;
	Display* _display;
	Window* _window;
	Array<World*> _worlds;

	u16 _width;
	u16 _height;

	bool _quit;
	bool _paused;

	u64 _frame_count;
	f64 _time_since_start;

	bool process_events(bool vsync);

	///
	Device(const DeviceOptions& opts, ConsoleServer& cs);

	/// Runs the engine.
	void run();

	/// Returns the number of command line parameters.
	int argc() const { return _device_options._argc; }

	/// Returns command line parameters.
	const char** argv() const { return (const char**)_device_options._argv; }

	/// Return the number of frames rendered.
	u64 frame_count() const;

	/// Returns the time in seconds since the the application started.
	f64 time_since_start() const;

	/// Quits the application.
	void quit();

	/// Pauses the engine.
	void pause();

	/// Unpauses the engine.
	void unpause();

	/// Returns the main window resolution.
	void resolution(u16& width, u16& height);

	/// Renders @a world using @a camera.
	void render(World& world, UnitId camera_unit);

	/// Creates a new world.
	World* create_world();

	/// Destroys the world @a w.
	void destroy_world(World& w);

	/// Returns the resource package @a id.
	ResourcePackage* create_resource_package(StringId64 id);

	/// Destroys the resource package @a rp.
	/// @note
	/// Resources are not automatically unloaded.
	/// You have to call ResourcePackage::unload() before destroying a package.
	void destroy_resource_package(ResourcePackage& rp);

	/// Reloads the resource @a type @a name.
	void reload(StringId64 type, StringId64 name);

	/// Logs @a msg to log file and console.
	void log(const char* msg);

private:

	// Disable copying
	Device(const Device&);
	Device& operator=(const Device&);
};

/// Runs the engine.
void run(const DeviceOptions& opts);

/// Returns the device.
Device* device();

} // namespace crown
