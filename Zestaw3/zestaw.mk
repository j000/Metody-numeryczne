# Copyright (C) 2018 Jarosław Rymut
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>

all: plot.zad1.png
all: plot.zad2.1.png
all: plot.zad2.2.png
all: plot.zad2.3.png
all: plot.zad2.4.png
all: plot.zad2.5.png

result.%.txt: %.x
	./$^ > $@

plot.%.png: gnu.plot result.%.txt
	gnuplot -e 'set output "$@"' -e 'filename="result.$*.txt"' -e 'my_title="$*"' gnu.plot

mostlyclean: clean_plots
.PHONY: clean_plots
clean_plots:
	$(RM) plot.*.png result.*.txt
