#include "vgm2pre.hpp"
#include "app.cpp"
#include "sub.ym2612.cpp"

/** open a file **/
void Prog::open(const lstring &files) {
	close();
	unsigned s = files.size();
	win->bar.setProgress(0);
	win->bar.bDo.setEnabled(false);
	if (s>0) {
		proc.init();
		unsigned i = 0;
		for (auto &fn : files) {
			win->bar.setProgress((unsigned)((100*++i)/s));
			win->bar.setStatus((string){"Processed ",fn});
			if (directory::exists(fn)) {
				proc.processDirectory(fn);
				/*MessageWindow()
					.setTitle(name)
					.setText({
						fn," is a directory!"
					})
					.warning();*/
			}
			else {
				string ext = extension(fn);
				if (ext=="vgm"||ext=="vgz") {
					proc.processFile(fn);
					//win->setTitle({notdir(fn)," - ", name});
				}
				else MessageWindow()
					.setTitle(name)
					.setText({
						"File \"",notdir(fn),"\" does not have a supported extension!"
					})
					.warning();
			}
		}
		win->setTitle({
			"Handling ",proc.filelist.size()," file(s)",
			" - ",name
		});
		if (proc.filelist.size()>0) {
			win->lvFiles.reset();
			string fl = "";
			for (auto &f : proc.filelist) {
				//fl.append((string){f,"\n"});
				win->lvFiles.append({"Ready",f});
			}
			win->lvFiles.autoSizeColumns();
			win->out.setText(fl);
			win->bar.setStatus((string){
				proc.filelist.size(),
				" file",(proc.filelist.size()!=1?"s":""),
				" ready for dumping"
			});
			win->bar.bDo.setEnabled(true);
			/*MessageWindow()
				.setTitle(name)
				.setText({
					"Instrument list ready for dumping!"
				})
				.information();*/
		}
		else win->bar.setStatus("No supported files found.");
	}
}

/** close a file **/
void Prog::close() {
	win->setTitle(name);
}

/** open the GUI **/
void Prog::interactiveMode(const lstring &files) {
	win = new Win;
	win->setVisible();
	win->setFocused();
	close();
	if (files.size()>0) open(files);
	Application::run();
}

/** print out program usage **/
void Prog::usage() {
	print(
		"Usage: vgm2pre [opts] [<infile> [<infile> [...]]]\n",
		"\tOptions include:\n",
		"\t-pOPN ??????\tToggle OPN preset output formats\n",
		"\t-eOPN\tUse extended OPN preset comparison\n"
		//"\t",argprefix,"eOPM\tUse extended OPM preset comparison\n",
		//"Graphical version soon!\n"
	);
	print(
		name,"\n",
		"author: apollolux\n",
		"license: ISC\n",
		"\n"
	);
}

/** initialize program variables **/
void Prog::init() {
	prog = this;
	name = "VGM2Pre";
	version = 1.0;
	cfg.dumpOPN[N::OPN::Types::VGI] = true;
	cfg.dumpOPN[N::OPN::Types::TFI] = true;
	cfg.dumpOPN[N::OPN::Types::TYI] = true;
	cfg.dumpOPN[N::OPN::Types::EIF] = true;
	cfg.dumpOPN[N::OPN::Types::DMP] = true;
	cfg.dumpOPN[N::OPN::Types::Y12] = true;
	cfg.dumpOPN[N::OPN::Types::GYB] = false;
	//cfg.disabledOPN[N::OPN::Types::Y12] = true;
	//cfg.disabledOPN[N::OPN::Types::GYB] = true;
	//cfg.dumpOPM[N::OPM::Types::OPM] = true;
	cfg.disabledOPM[N::OPM::Types::OPM] = true;
	Application::setName(name);
}

/** constructor **/
Prog::Prog(int argc, char **argv) {
	init();
	lstring files;
	if (argc>1) {
		for (unsigned i=1; i<argc; ++i) {
			if (directory::exists(argv[i])) files.append(argv[i]);
			else if (file::exists(argv[i])) files.append(argv[i]);
		}
		interactiveMode(files);
		return;
	}
	else if (argc==1) {
		interactiveMode(files);
		return;
	}
	usage();
}


int main(int argc, char **argv) {
	#if defined(PLATFORM_WINDOWS)
	utf8_args(argc, argv);
	#endif
	new Prog(argc, argv);
	delete prog;
	return 0;
}
