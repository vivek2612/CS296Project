.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
LATEX = latex
DVIPDF = dvipdf
######################################
# Project Name (generate executable with this name)
TARGET_EXEC = RubeGoldbergMachine
TARGET_PLOTS = RubeGoldbergMachinePlots

# Project Paths
PROJECT_ROOT = $(shell pwd)
DATADIR = $(PROJECT_ROOT)/data
PLOTDIR = $(PROJECT_ROOT)/plots
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIREXEC = $(PROJECT_ROOT)/src_exec
SRCDIRPLOTS = $(PROJECT_ROOT)/src_plots
OBJDIR = $(PROJECT_ROOT)/obj
OBJDIRPLOTS = $(PROJECT_ROOT)/obj_plots
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
DATADIR = $(PROJECT_ROOT)/data
SCRIP = $(PROJECT_ROOT)/scripts
PLOTDIR = $(PROJECT_ROOT)/plots
BOX2DLIBRARY = $(PROJECT_ROOT)/external/lib/libBox2D.a
BOX2DINCLUDE = $(PROJECT_ROOT)/external/include/Box2D
DVIFILE := $(LATEXFILE:$(DOCDIR)/%.tex=$(PROJECT_ROOT)/%.dvi)

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall 
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCSEXEC := $(wildcard $(SRCDIREXEC)/*.cpp)
INCSEXEC := $(wildcard $(SRCDIREXEC)/*.hpp)
OBJS_EXEC := $(SRCSEXEC:$(SRCDIREXEC)/%.cpp=$(OBJDIR)/%.o)

SRCSPLOTS := $(wildcard $(SRCDIRPLOTS)/*.cpp)
INCSPLOTS := $(wildcard $(SRCDIRPLOTS)/*.hpp)
OBJS_PLOTS := $(SRCSPLOTS:$(SRCDIRPLOTS)/%.cpp=$(OBJDIRPLOTS)/%.o)


.PHONY: all setup doc clean distclean compileb2D

all: setup report doc $(BINDIR)/$(TARGET_EXEC)

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p obj_plots

$(BINDIR)/$(TARGET_PLOTS): compileb2D setup $(OBJS_PLOTS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS_PLOTS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err
	
$(BINDIR)/$(TARGET_EXEC): compileb2D setup $(OBJS_EXEC)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS_EXEC) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS_EXEC:.o=.d)
-include $(OBJS_PLOTS:.o=.d)

$(OBJS_EXEC):  $(OBJDIR)/%.o : $(SRCDIREXEC)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

$(OBJS_PLOTS): $(OBJDIRPLOTS)/%.o : $(SRCDIRPLOTS)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err	

compileb2D: 
	@cd $(EXTERNAL_ROOT)/src ; tar -zxvf Box2D.tgz ; \
	cd Box2D; rm -rf build296; mkdir build296; cd build296; \
	cmake -DCMAKE_BUILD_TYPE=Release ../. ; \
	make ; make install;

datadir:
	@chmod +x $(SCRIP)/*.sh
	@mkdir -p $(DATADIR) 
	@mkdir -p $(PLOTDIR)

plots : datadir $(BINDIR)/$(TARGET_PLOTS)
	@ cd $(SCRIP);$(SCRIP)/gen_data_csv.sh;$(SCRIP)/helper6.sh;$(SCRIP)/helper5.sh;gnuplot $(SCRIP)/g14_plot01.gpt;gnuplot $(SCRIP)/g14_plot02.gpt;gnuplot $(SCRIP)/g14_plot03.gpt;gnuplot $(SCRIP)/g14_plot04.gpt;gnuplot $(SCRIP)/g14_plot05.gpt;gnuplot $(SCRIP)/g14_plot06.gpt;
	@ rm -rf $(DATADIR)/Temp*.csv $(DATADIR)/*~ $(SCRIP)/*~ $(DATADIR)/*~
	@ rm -rf $(DATADIR)

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

report: 
	@cd $(DOCDIR); $(LATEX) RubeGoldbergAnalysis.tex; $(DVIPDF) RubeGoldbergAnalysis.dvi; $(RM) -rf *.dvi *~ *.aux *.log
	@$(RM) -rf *.dvi *~ *.aux *.log

install : setup report doc htmlDoc $(BINDIR)/$(TARGET_EXEC)

dist : clean
	@ cd ../ ; tar zcvf cs296_g14_project.tar.gz CS296Project ;

htmlDoc : plots
	@ cd $(SCRIP) ; python3 g14_gen_html.py;

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) $(OBJDIRPLOTS) $(BINDIR) *~ $(DEPS) $(SRCDIR)/*~ $(DOCDIR)/*.pdf $(DOCDIR)/*.log $(DOCDIR)/*.aux $(DOCDIR)/*~ $(DOCDIR)/*.dvi $(DOCDIR)/*.html $(DATADIR) $(PLOTDIR) $(DOCDIR)/html
	@$(RM) -rf $(PROJECT_ROOT)/external/include $(PROJECT_ROOT)/external/lib $(PROJECT_ROOT)/external/src/Box2D
	@$(RM) -rf *.dat *.out
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html
