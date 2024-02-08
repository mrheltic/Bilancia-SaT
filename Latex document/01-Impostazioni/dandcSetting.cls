

% Identificazione della classe
\ProvidesClass{01-Impostazioni/dandcSetting}


% Pkgs
\RequirePackage{fancyhdr}
\RequirePackage{lastpage}
\usepackage[fit, breakall]{truncate}

% Impostazioni
\newif\if@color\@colorfalse
\newif\if@pdf\@pdffalse

\DeclareOption{color}{\@colortrue}
\DeclareOption{pdftex}{\@pdftrue}
\DeclareOption{twocolumn}{\OptionNotUsed}
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
\ProcessOptions\relax

\if@pdf
\RequirePackage[pdftex]{graphicx}
\else
\RequirePackage{graphicx}
\fi
\LoadClass[a4paper]{article}

% Margini

\topmargin -50mm
% \headsep 20mm
\headheight 60mm

\textheight 220mm 
\textwidth 150mm

\hoffset -15mm
% % \voffset -15mm

 \leftmargin 15mm
 \rightmargin 15mm


% Colori
\if@color
\RequirePackage{color}
\fi 

% Intestazione
\pagestyle{fancy}


\renewcommand{\footrulewidth}{0.4pt}%
