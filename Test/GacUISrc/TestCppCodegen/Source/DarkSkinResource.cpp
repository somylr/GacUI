﻿#include "DarkSkinIncludes.h"

namespace vl
{
	namespace presentation
	{
		namespace user_resource
		{
			using namespace collections;
			using namespace stream;
			using namespace controls;

			class DarkSkinResourceReader
			{
			public:
				static const vint parserBufferLength = 1288; // 2949 bytes before compressing
				static const vint parserBufferBlock = 1024;
				static const vint parserBufferRemain = 264;
				static const vint parserBufferRows = 2;
				static const char* parserBuffer[2];

				static void ReadToStream(vl::stream::MemoryStream& stream)
				{
					DecompressStream(parserBuffer, true, parserBufferRows, parserBufferBlock, parserBufferRemain, stream);
				}
			};

			const char* DarkSkinResourceReader::parserBuffer[] = {
				"\x85\x0B\x00\x00\x00\x05\x00\x00\x06\x00\x01\x82\x80\x03\x03\x82\x81\x82\x01\xC4\x2F\x23\x38\x06\x81\x81\x86\x01\xC9\x2E\x33\x34\x39\x32\x37\x31\x65\x00\x8E\x9A\x80\x03\x2B\x30\x39\x69\x70\x34\x2D\x0E\x80\x00\x93\x88\x13\x95\x97\x85\x33\x2C\x39\x3C\x36\x65\x04\x25\x92\x91\x84\x29\x32\x3C\x74\x0F\x25\x9A\x91\x83\x20\x37\x30\x73\x73\x0E\x21\x3D\x35\x32\x29\x32\x63\x6F\x32\x24\x35\x94\x81\x92\x88\x06\xD0\x84\x21\x32\x3B\x37\x29\x35\x69\x6E\x01\x0D\xA5\x90\x09\xAE\x81\x42\x40\xA5\x2C\x39\xAD\x32\x85\x31\x75\x45\xAE\x34\x3E\x5D\x91\xB7\x80\x3C\x67\xBE\x1C\x13\x27\x37\xB5\x32\x6B\xAF\x33\xAD\x9F\x95\x33\x39\xBD\x2E\xB0\xA0\x0E\x34\xA5\x31\x1E\x11\x23\x44\x25\x26\x31\x35\x38\x36\x3A\x2D\x4F\x36\x25\x32\x38\x90\x33\x32\x22\x73\x89\xAC\x3A\xA6\x1F\x10\x23\xA0\xA1\xFC\x0F\x1B\xCD\xCF\xD0\xBE\x30\x80\xFD\xA3\xC5\xC7\xC3\x11\x29\x63\xC8\xB4\x29\x36\xB9\xCB\xC9\xCA\x69\x17\xD9\xDC\x15\xD2\x3A\xCF\xD0\xA2\xA4\xEF\x3C\xCE\xDC\x1E\x31\x35\xBD\x9E\xF0\x10\x17\x19\x23\x21\x21\xA3\xC7\xC9\xE7\xD1\xC5\x33\xB9\x17\xA8\xFE\x97\xF2\xBD\xA4\x05\x92\xEF\x01\xC7\x21\x23\x37\x20\xBD\xBA\x37\x66\x69\x27\x2D\xAB\xAE\x84\x84\x83\xEF\xC3\x30\x30\x35\x03\x99\x93\x93\x06\xF8\xF2\xF0\x35\xBD\x34\x38\x39\x7E\x73\x15\x18\x19\x14\x25\x45\x81\x42\x54\x56\x58\x56\x1B\x47\x73\x1F\x19\x1D\x72\x18\x4E\x0B\x18\xF3\x74\x46\x42\x85\x03\x56\x83\x51\x51\x50\x43\x42\x55\x82\x57\x59\x58\x86\x40\xF8\x43\x48\x7E\x13\x4A\x6D\x11\x18\x1B\x12\x63\x1C\x19\x1D\x97\x5E\x5E\x42\x8C\x00\x2E\x0E\x0B\x0B\x36\xB8\x87\x8E\x78\x63\x15\x19\x12\x0B\x68\x23\x81\x41\x04\x25\x44\x91\x43\x51\x66\x30\x43\x1B\x6C\x76\x6D\x8F\x8B\x65\x39\x25\x41\x95\x40\x39\x95\x97\x8C\x92\x4A\x8C\x9E\x1B\x0B\x54\x39\x10\x1E\x59\x7E\x5F\x41\x48\x1D\x4A\x73\x1F\x0B\x11\x75\x29\x18\x96\x6C\xB4\x6E\x10\x17\x8B\x67\x19\x50\x92\x90\x00\x20\x76\x42\x9D\x53\x0F\x81\x85\x19\x46\x03\x77\x66\x1C\x1C\x43\x4C\x45\x9E\x10\x98\x4D\x53\x02\x25\x48\xA1\x40\x14\x00\x89\x5E\x7D\x1A\x30\x64\x1D\x7A\x41\xF5\x4E\x4C\x4E\x41\x97\xBE\x40\x52\x50\x85\x47\x59\x53\x52\x31\x25\x44\x0A\xA8\x02\x64\x19\x83\x1C\x0B\xBA\x0A\x0E\x10\x6F\x34\x14\x99\x1B\x1E\x72\x13\x70\x1B\x42\x35\x1E\xAA\x5D\x36\x7E\x7F\x4C\x1D\x65\x18\x05\x4A\xAF\x01\x66\xA5\x54\xAA\x59\x6A\xA5\xAF\xAD\x6E\x39\xA0\x1F\xAE\x65\x1A\x05\x4A\xB3\xC1\xA7\xA9\xAA\x0E\x43\x28\x18\x53\x1A\xAC\xB8\x1A\xB0\xB3\x25\x25\x4D\xB5\xB4\xC3\x93\xB5\xB7\xB5\x49\x3C\xAD\x19\x58\x63\x2B\x17\x1A\xAC\x75\x2E\x14\x1B\xB6\x61\x3C\xA0\xB6\x41\xF3\x82\xBB\x18\xB1\x6E\x2A\xAD\x7E\x18\x6F\x19\xB0\xBC\xAF\x1F\x25\x41\xC0\xB8\xF7\xA2\xB5\x1C\x45\x6F\x2D\x17\x78\x1D\xB2\xAC\x1F\xBD\x19\x97\x83\x47\xA6\xBD\xF8\xAA\xA4\x16\xB5\x45\x5C\x05\x4A\xC6\x04\xD5\xCA\x0F\x54\xBC\x90\x19\x19\xBA\x94\x4F\xC3\xC2\x41\x27\xD4\xC3\xB7\x59\x69\x78\x54\x1C\x13\x61\x22\x13\x5B\xC3\x21\x25\x45\xCD\xC7\x2B\xCB\x4D\xCB\x5A\x36\x78\x4E\xBD\x19\xBA\xB1\xB5\x18\x08\x25\x44\xD8\xCD\xB1\x1F\xFA\xCA\x58\x1D\x56\x29\x15\x1B\x1D\x25\xC0\xDB\xB2\xD0\xA3\x8E\x45\xD4\x00\x2A\xC8\xD5\x10\x1E\x70\x16\x44\x19\x56\x67\x0A\x6F\xA5\xBC\x4A\x4F\xC3\xBF\x40\xF5\x92\xB8\xD3\x11\xEC\xB0\x1F\xCD\xD0\x00\xC2\xC5\xAA\xDA\xF9\xBA\x08\x11\xAC\xB3\x88\x1E\xD4\x4C\x0F\xD9\x05\x4A\xDF\x47\xF5\xD7\xDF\x47\xB3\xA6\xDF\xB3\xDC\xE1\x88\xD8\x10\x15\x72\x23\x7B\x19\xD4\x70\xC3\xD5\xD0\xE2\x05\xC8\xD5\xB8\xD0\xE8\xAA\xBC\xBA\xBB\x0F\xD7\x05\x4A\xE7\x81\xEA\xA0\xCE\xCC\x0E\xD2\xDC\xB2\x08\x25\x68\xE1\xEA\x0E\x4C\x0B\x64\x1C\xDE\x6C\x34\xA6\xAC\x99\xC9\xA6\xE2\xD2\x09\x25\x78\xEB\xE8\x13\x69\x14\x4D\xD3\xD3\x75\x6F\x8D\x1A\x1B\x48\x25\x11\x1B\x9F\x86\xCE\x49\xD9\xE2\x75\xFC\xEE\xEE\xD3\x77\x26\xC2\xDF\xEA\x4D\x38\x55\x1D\x58\x72\x07\xB4\xEF\xC3\x46\xC6\x4D\xF5\xD6\x75\xD5\xFE\x19\x1D\x97\xE7\xB3\xEC\xAE\xB6\xFC\xAE\x05\x49\xEB\xD4\xF6\xF7\x14\xCB\xA9\x1E\xA8\xE4\x53\xFC\xAA\xEA\x41\xF7\xE0\xFA\xA9\x13\x8E\x73\x64\x5A\x1B\x65\x1D\x64\x1D\x6F\x65\x7F\x32\x1D\x05\x24\x07\x8B\x74\xA3\x6F\x0B\x5D\x00\x58\x7F\x61\x09\x86\x21\x04\xFA\x7A\x06\x29\x07\x7C\x36\xDA\x68\x7D\xE4\x23\x05\x24\x0E\xAB\x72\x0A\xEA\x28\x0F\xEB\x04\x71\x77\x0C\xB5\x71\x72\x1C\x66\x21\x0A\x94\x80\x76\x36\x3F\x71\x7A\xE9\x66\x80\x02\x94\x7E\x63\x29\x28\x0A\x29\x74\x08\x2C\x1D\x4B\x05\x0D\x3C\x0F\x66",
				"\x83\x06\x20\x88\x0B\xE0\x60\x27\xFF\x41\x87\x26\x03\x8F\x0E\xB6\x31\x81\x83\x81\x13\x84\x6E\x16\x71\x64\x11\x32\x50\x0E\x32\x2F\x0F\x0E\x27\x85\x83\x06\x25\x2B\x8B\xD5\x54\x09\x66\xC5\x67\x78\xFD\x4C\x55\x03\x92\x25\x8E\x8B\x31\x69\x78\xBD\x34\x83\x5A\x01\x8E\x7C\x0E\x0F\x7F\x5A\x41\x72\x84\x82\x2A\x2F\x0B\x38\x14\x20\x24\x1C\x70\x74\x2C\x3A\x01\x0D\x32\x57\x94\x66\xCD\x6C\x88\x68\x3B\xB8\x8C\x61\x21\x26\x87\xC3\x29\x05\x24\x46\x9E\x8F\x8E\x6C\x19\x8D\x48\x53\x8F\x0D\x2A\x97\x8E\x0D\x8A\x91\x87\xC9\x03\x29\x64\x28\xBA\x06\x90\x91\x88\x90\x1C\x62\x75\x0F\x87\x7A\x76\x20\xA7\x95\x8C\x24\x92\x9B\x8F\xF8\x43\x87\x7C\x59\x8C\x58\x10\x83\x22\x88\x4F\xA0\x94\x95\x7C\x92\x7C\xAF\x72\x0F\x61\x2E\x86\x26\x97\xAA\x87\x92\x1E\xFD\x6F\x6E\x42\xB5\x68\x94\xB3\x30\x0E\x20\x8E\x27\x66\xAC\x76\x95\x92\x2D\x99\x91\xE4\x67\x62\x21\xE5\x55\x77\x98\x00\x45\x0F\x0B\xD2\x7E\x21\x4E\x8C\x7A\x55\x56\x0D\x86\xDE\x6E\x5C\x6F\x18\x80\x76\x20\xE7\x94\x81\x38\xA4\x85\x75\x69\x87\x73\x75\x56\x0C\x72\xE3\x63\x82\x68\x60\x46\x26\x9E\x14\x97\x09\x56\x56\x80\x87\xC8\x4D\x28",
				};

			class DarkSkinResourceLoaderPlugin : public Object, public IGuiPlugin
			{
			public:

				GUI_PLUGIN_NAME(GacGen_DarkSkinResourceLoader)
				{
					GUI_PLUGIN_DEPEND(GacUI_Res_Resource);
					GUI_PLUGIN_DEPEND(GacUI_Res_TypeResolvers);
#ifndef VCZH_DEBUG_NO_REFLECTION
					GUI_PLUGIN_DEPEND(GacUI_Instance_Reflection);
					GUI_PLUGIN_DEPEND(GacUI_Compiler_WorkflowTypeResolvers);
#endif
				}

				void Load()override
				{
					List<GuiResourceError> errors;
					MemoryStream resourceStream;
					DarkSkinResourceReader::ReadToStream(resourceStream);
					resourceStream.SeekFromBegin(0);
					auto resource = GuiResource::LoadPrecompiledBinary(resourceStream, errors);
					GetResourceManager()->SetResource(L"DarkSkin", resource, GuiResourceUsage::InstanceClass);
				}

				void Unload()override
				{
				}
			};
			GUI_REGISTER_PLUGIN(DarkSkinResourceLoaderPlugin)
		}
	}
}