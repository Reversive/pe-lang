import pefile
import json
import sys
import os

class PEAnalyzer:
    def __init__(self, file_path):
        self.file_path = file_path.replace('\\', '/')
        if not os.path.isfile(self.file_path):
            raise ValueError("Couldn't find the target file")
        else:
            self.pe = pefile.PE(file_path)

    def analyze(self):
        analysis = {
            "file_header": self._file_header(),
            "optional_header": self._optional_header(),
            "sections": self._sections(),
            "imports": self._imports(),
            "exports": self._exports(),
        }
        return json.dumps(analysis, indent=2)

    def _file_header(self):
        return {
            "machine": self.pe.FILE_HEADER.Machine,
            "number_of_sections": self.pe.FILE_HEADER.NumberOfSections,
            "time_date_stamp": self.pe.FILE_HEADER.dump_dict()["TimeDateStamp"]["Value"].split("[")[1][:-1],
            "characteristics": hex(self.pe.FILE_HEADER.Characteristics),
        }

    def _optional_header(self):
        return {
            "aoep": hex(self.pe.OPTIONAL_HEADER.AddressOfEntryPoint),
            "image_base": hex(self.pe.OPTIONAL_HEADER.ImageBase),
            "section_alignment": self.pe.OPTIONAL_HEADER.SectionAlignment,
            "file_alignment": self.pe.OPTIONAL_HEADER.FileAlignment,
            "subsystem": self.pe.OPTIONAL_HEADER.Subsystem,
        }

    def _sections(self):
        sections = []
        for section in self.pe.sections:
            sections.append({
                "name": section.Name.decode().rstrip("\x00"),
                "virtual_address": hex(section.VirtualAddress),
                "virtual_size": section.Misc_VirtualSize,
                "raw_data_size": section.SizeOfRawData,
                "characteristics": hex(section.Characteristics),
            })
        return sections

    def _imports(self):
        imports = []
        if hasattr(self.pe, "DIRECTORY_ENTRY_IMPORT"):
            for entry in self.pe.DIRECTORY_ENTRY_IMPORT:
                imports.append({
                    "dll": entry.dll.decode(),
                    "functions": [
                        {"address": f"0x{imp.address:x}", "name": imp.name.decode()}
                        for imp in entry.imports
                    ],
                })
        return imports

    def _exports(self):
        exports = []
        if hasattr(self.pe, "DIRECTORY_ENTRY_EXPORT"):
            exports.append({
                "dll_name": self.pe.DIRECTORY_ENTRY_EXPORT.dll.decode(),
                "functions": [
                    {"address": f"0x{exp.address:x}", "name": exp.name.decode()}
                    for exp in self.pe.DIRECTORY_ENTRY_EXPORT.symbols
                ],
            })
        return exports