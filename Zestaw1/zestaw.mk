# Copyright (C) 2018 Jarosław Rymut
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>

HELPERS += $(wildcard sin*.cpp)
FILES := $(filter-out $(HELPERS),$(wildcard *.cpp))

all: plot.sin1.png
all: plot.sin2.png
all: plot.sin3.png
# all: plot.sin4.png
all: plot.sin1b.png

result.%.txt: plot.%.x
	./$^ > $@

plot.%.png: gnu.plot result.%.txt
	gnuplot -e 'set output "$@"' -e 'filename="result.$*.txt"' gnu.plot

mostlyclean: clean_plot
.PHONY: clean_plot
clean_plot:
	$(RM) plot.*.png result.*.txt
